#include <functional>
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QTimer>
#include <QDateTime>
#include "chatserver.h"
#include "serverworker.h"

ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent)
    , m_currentUserId(0)
    , m_currentMessageId(0)
{}
//------------------------------------------------------------------------------------------
void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWorker *worker = new ServerWorker(this);
    if (!worker->setSocketDescriptor(socketDescriptor))
    {
        worker->deleteLater();
        return;
    }
    connect(worker, &ServerWorker::disconnectedFromClient
            , this, std::bind(&ChatServer::userDisconnected
            , this, worker));
    connect(worker, &ServerWorker::error
            , this, std::bind(&ChatServer::userError
            , this, worker));
    connect(worker, &ServerWorker::jsonReceived
            , this, std::bind(&ChatServer::jsonReceived
            , this, worker, std::placeholders::_1));
    connect(worker, &ServerWorker::logMessage
            , this, &ChatServer::logMessage);
    m_clients.append(worker);
    emit logMessage(QStringLiteral("New client Connected"));
}
//------------------------------------------------------------------------------------------
void ChatServer::sendJson(ServerWorker *destination, const QJsonObject &message)
{
    Q_ASSERT(destination);
    destination->sendJson(message);
}
//------------------------------------------------------------------------------------------
void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    for (ServerWorker *worker : m_clients)
    {
        Q_ASSERT(worker);
        if (worker == exclude)
            continue;
        sendJson(worker, message);
    }
}
//------------------------------------------------------------------------------------------
void ChatServer::jsonReceived(ServerWorker *sender, const QJsonObject &doc)
{
    Q_ASSERT(sender);
    emit logMessage(QLatin1String("JSON received ")
                    + QString::fromUtf8(QJsonDocument(doc).toJson()));
    // If it is not a logged in user
    if (sender->id() == 0)
        return jsonFromLoggedOut(sender, doc);
    jsonFromLoggedIn(sender, doc);
}
//------------------------------------------------------------------------------------------
void ChatServer::userDisconnected(ServerWorker *sender)
{
    m_clients.removeAll(sender);
    const int user_id = sender->id();
    const QString username = sender->userName();
    if (user_id != 0)
    {
        m_blankIds.append(user_id);
        QJsonObject disconnectedMessage;
        disconnectedMessage[QStringLiteral("type")] = QStringLiteral("userleft");
        disconnectedMessage[QStringLiteral("userid")] = user_id;
        disconnectedMessage[QStringLiteral("username")] = username;
        broadcast(disconnectedMessage, nullptr);
        emit logMessage(username + QLatin1String(" disconnected"));
    }
    sender->deleteLater();
}
//------------------------------------------------------------------------------------------
void ChatServer::userError(ServerWorker *sender)
{
    Q_UNUSED(sender)
    emit logMessage(QLatin1String("Error from ") + sender->userName());
}
//------------------------------------------------------------------------------------------
void ChatServer::stopServer()
{
    for (ServerWorker *worker : m_clients)
    {
        worker->disconnectFromClient();
    }
    m_currentUserId = 0;
    m_blankIds.clear();
    m_currentMessageId = 0;
    close();
}
//------------------------------------------------------------------------------------------
void ChatServer::jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &docObj)
{
    // Getting current time
    uint time = QDateTime::currentDateTime().toSecsSinceEpoch();
    Q_ASSERT(sender);
    const QJsonValue type_val = docObj.value(QLatin1String("type"));
    if (type_val.isNull() || !type_val.isString())
        return;
    if (type_val.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) != 0)
        return;
    const QJsonValue username_val = docObj.value(QLatin1String("username"));
    if (username_val.isNull() || !username_val.isString())
        return;
    const QString new_username = username_val.toString().simplified();
    if (new_username.isEmpty())
        return;
    for (ServerWorker *worker : qAsConst(m_clients))
    {
        if (worker == sender)
            continue;
        if (worker->userName().compare(new_username, Qt::CaseInsensitive) == 0)
        {
            // Response for new client
            QJsonObject message;
            message[QStringLiteral("type")] = QStringLiteral("login");
            message[QStringLiteral("status")] = StatusCode::DUPLICATE;
            sendJson(sender, message);
            return;
        }
    }
    // Here we avoid "blank" ids, we don't increment m_currentUserId
    // if we have free minor values
    if (m_blankIds.isEmpty())
        sender->setId(++m_currentUserId);
    else
    { // Always take first element and remove it
        sender->setId(m_blankIds.first());
        m_blankIds.removeFirst();
    }
    sender->setUserName(new_username);
    sender->setJoinedTime(time);
    // Response for new client
    QJsonObject success_message;
    success_message[QStringLiteral("type")] = QStringLiteral("login");
    success_message[QStringLiteral("status")] = StatusCode::SUCCESS;
    success_message[QStringLiteral("userid")] = sender->id();
    success_message[QStringLiteral("joinedtime")] = static_cast<int>(sender->joinedTime());
    QJsonArray connected_clients;
    for (ServerWorker *worker : m_clients)
    {
        if (worker == sender)
            continue;
        QJsonObject to_client;
        to_client[QStringLiteral("id")] = worker->id();
        to_client[QStringLiteral("username")] = worker->userName();
        to_client[QStringLiteral("joinedtime")] = static_cast<int>(worker->joinedTime());
        connected_clients.append(to_client);
    }
    success_message[QStringLiteral("members")] = connected_clients;
    sendJson(sender, success_message);
    // Notify clients about new user
    QJsonObject connected_message;
    connected_message[QStringLiteral("type")] = QStringLiteral("newuser");
    connected_message[QStringLiteral("userid")] = sender->id();
    connected_message[QStringLiteral("joinedtime")] = static_cast<int>(sender->joinedTime());
    connected_message[QStringLiteral("username")] = new_username;
    broadcast(connected_message, sender);
}
//------------------------------------------------------------------------------------------
void ChatServer::jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &docObj)
{
    Q_ASSERT(sender);

    const QJsonValue type_val = docObj.value(QLatin1String("type"));
    if (type_val.isNull() || !type_val.isString())
        return;

    if (type_val.toString().compare(QLatin1String("textmsg"), Qt::CaseInsensitive) != 0)
        return;

    const QJsonValue time_val = docObj.value(QLatin1String("time"));
    if (time_val.isNull())
        return;


    const QJsonValue text_val = docObj.value(QLatin1String("text"));
    if (text_val.isNull() || !text_val.isString())
        return;
    const QString text = text_val.toString();
    if (text.isEmpty())
        return;

    const QJsonValue reply_val = docObj.value(QLatin1String("reply"));
    if (reply_val.isNull())
        return;

    const QJsonValue replytext_val = docObj.value(QLatin1String("replytext"));
    if (replytext_val.isNull() || !replytext_val.isString())
        return;

    m_currentMessageId++;
    // Response for message sender
    QJsonObject message_confirm;
    message_confirm[QStringLiteral("type")] = QStringLiteral("msgconfirm");
    message_confirm[QStringLiteral("msgid")] = m_currentMessageId;
    sendJson(sender, message_confirm);

    // Broadcast message
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("textmsg");
    message[QStringLiteral("time")] = time_val;
    message[QStringLiteral("msgid")] = m_currentMessageId;
    message[QStringLiteral("userid")] = sender->id();
    message[QStringLiteral("username")] = sender->userName();
    message[QStringLiteral("text")] = text;
    message[QStringLiteral("reply")] = reply_val;
    message[QStringLiteral("replytext")] = replytext_val;
    broadcast(message, sender);
}
