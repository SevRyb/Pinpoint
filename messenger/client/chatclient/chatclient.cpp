#include <QTcpSocket>
#include <QDataStream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QVector>
#include "chatclient.h"
#include "chatmember.h"
#include "textmessage.h"

ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
    , m_clientSocket(new QTcpSocket(this))
    , m_loggedIn(false)
{
    // Forward the connected and disconnected signals
    connect(m_clientSocket, &QTcpSocket::connected, this, &ChatClient::connected);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &ChatClient::disconnected);
    // connect readyRead() to the slot that will take care of reading the data in
    connect(m_clientSocket, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    // Forward the error signal, QOverload is necessary as error() is overloaded, see the Qt docs
    connect(m_clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ChatClient::error);
    // Reset the m_loggedIn variable when we disconnec. Since the operation is trivial we use a lambda instead of creating another slot
    connect(m_clientSocket, &QTcpSocket::disconnected, this, [this]()->void{m_loggedIn = false;});
}
//------------------------------------------------------------------------------------------
void ChatClient::login(const QString &userName)
{
    if (m_clientSocket->state() == QAbstractSocket::ConnectedState)
    { // if the client is connected
        // create a QDataStream operating on the socket
        QDataStream clientStream(m_clientSocket);
        // set the version so that programs compiled with different versions of Qt can agree on how to serialise
        clientStream.setVersion(QDataStream::Qt_5_7);
        // Create the JSON we want to send
        QJsonObject message;
        message[QStringLiteral("type")] = QStringLiteral("login");
        message[QStringLiteral("username")] = userName;
        // Send the JSON using QDataStream
        clientStream << QJsonDocument(message).toJson(QJsonDocument::Compact);
    }
}
//------------------------------------------------------------------------------------------
void ChatClient::sendMessage(TextMessage *text_message)
{
    if (text_message->text().isEmpty())
        return; // We don't send empty messages
    // Create a QDataStream operating on the socket
    QDataStream clientStream(m_clientSocket);
    // Set the version so that programs compiled with different versions of Qt can agree on how to serialise
    clientStream.setVersion(QDataStream::Qt_5_7);

    // Create the JSON we want to send
    QJsonObject message;
    message[QStringLiteral("type")] = QStringLiteral("textmsg");
    message[QStringLiteral("time")] = (int) text_message->time();
    message[QStringLiteral("text")] = text_message->text();
    message[QStringLiteral("reply")] = text_message->replyId();
    message[QStringLiteral("replytext")] = text_message->replyText();
    m_currentTextMessage = text_message;
    // Send the JSON using QDataStream
    clientStream << QJsonDocument(message).toJson();
}
//------------------------------------------------------------------------------------------
void ChatClient::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}
//------------------------------------------------------------------------------------------
void ChatClient::jsonReceived(const QJsonObject &docObj)
{
    // Actions depend on the type of message
    const QJsonValue type_val = docObj.value(QLatin1String("type"));
    if (type_val.isNull() || !type_val.isString())
        return; // a message with no type was received so we just ignore it

    if (type_val.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) == 0)
    { //It's a login message

        if (m_loggedIn)
            return; // if we are already logged in we ignore

        // the success field will contain the result of our attempt to login
        const QJsonValue result_val = docObj.value(QLatin1String("status"));
        if (result_val.isNull())
            return; // the message had no success field so we ignore
        const StatusCode login_status = static_cast<StatusCode>(result_val.toInt(-1));
        if (login_status == StatusCode::SUCCESS)
        {
            // We logged in succesfully and we notify it via the loggedIn signal
            // We extract user id
            const QJsonValue userid_val = docObj.value(QLatin1String("userid"));
            const int userid = static_cast<int>(userid_val.toInt(0));
            const QJsonValue joined_time_val = docObj.value(QLatin1String("joinedtime"));
            const uint joined_time = static_cast<uint>(joined_time_val.toInt(0));

            const QJsonValue members_val = docObj.value(QLatin1String("members"));
            if (!members_val.isArray())
                return;
            const QJsonArray members = members_val.toArray();

            QVector<ChatMember*> chat_members;
            for (const QJsonValue &member_val : members)
            {
                QJsonObject member = member_val.toObject();
                const QString username = member.value(QLatin1String("username")).toString();
                const int id = member.value(QLatin1String("id")).toInt(0);
                const uint time =  static_cast<uint>(member.value(QLatin1String("joinedtime")).toInt(0));
                chat_members.append(new ChatMember(username, id, time));
            }
            emit loggedIn(userid, joined_time, chat_members);
            return;
        }
        // The login attempt failed we notify it via the loginError signal
        emit loginError(login_status);
    }
    else if (type_val.toString().compare(QLatin1String("textmsg"), Qt::CaseInsensitive) == 0)
    { //It's a chat message

        // Message Time
        const QJsonValue time_val = docObj.value(QLatin1String("time"));
        if (time_val.isNull())
            return;
        // Message Id
        const QJsonValue msg_id_val = docObj.value(QLatin1String("msgid"));
        if (msg_id_val.isNull())
            return;
        // Sender Id
        const QJsonValue sender_id_val = docObj.value(QLatin1String("userid"));
        if (sender_id_val.isNull())
            return;
        // Sender Username
        const QJsonValue sender_username_val = docObj.value(QLatin1String("username"));
        if (sender_username_val.isNull() || !sender_username_val.isString())
            return;
        // Message Text
        const QJsonValue text_val = docObj.value(QLatin1String("text"));
        if (text_val.isNull() || !text_val.isString())
            return;
        // Reply Id
        const QJsonValue reply_id_val = docObj.value(QLatin1String("replyid"));
        if (reply_id_val.isNull())
            return;
        if (reply_id_val.toInt() == 0)
        {
            // Notify a new message was received via the messageReceived signal
            TextMessage *message = new TextMessage(MessageType::TEXT, (uint) time_val.toInt(0),
                                                   text_val.toString(), sender_username_val.toString(),
                                                   sender_id_val.toInt(), reply_id_val.toInt());
            message->setId(msg_id_val.toInt());
            emit messageReceived(message);
            return;
        }

        // Reply Text
        const QJsonValue reply_text_val = docObj.value(QLatin1String("replytext"));
        if (reply_text_val.isNull() || !reply_text_val.isString())
            return;


    }
    else if (type_val.toString().compare(QLatin1String("msgconfirm"), Qt::CaseInsensitive) == 0)
    { //It's a response on sending a chat message
        const QJsonValue msgid_val = docObj.value(QLatin1String("msgid"));
        if (msgid_val.isNull())
            return;
        m_currentTextMessage->setId(msgid_val.toInt());
    }
    // User Joined
    else if (type_val.toString().compare(QLatin1String("newuser"), Qt::CaseInsensitive) == 0)
    { // A user joined the chat
        // We extract the id of the new user
        const QJsonValue userid_val = docObj.value(QLatin1String("userid"));
        const int userid = static_cast<int>(userid_val.toInt(0));
        if (userid == 0)
            return;
        const QJsonValue joined_time_val = docObj.value(QLatin1String("joinedtime"));
        const uint joined_time = static_cast<uint>(joined_time_val.toInt(0));
        // We extract the username of the new user
        const QJsonValue username_val = docObj.value(QLatin1String("username"));
        if (username_val.isNull() || !username_val.isString())
            return; // the username was invalid so we ignore
        // We notify of the new user via the userJoined signal
        emit userJoined(new ChatMember(username_val.toString(), userid, joined_time));
    }
    // User Left
    else if (type_val.toString().compare(QLatin1String("userleft"), Qt::CaseInsensitive) == 0)
    { // A user left the chat
         // We extract the userid and username of the new user
        const QJsonValue userid_val = docObj.value(QLatin1String("userid"));
        const int userid = static_cast<int>(userid_val.toInt(0));
        if (userid == 0)
            return; // the username was invalid so we ignore
        const QJsonValue username_val = docObj.value(QLatin1String("username"));
        if (username_val.isNull() || !username_val.isString())
            return; // the username was invalid so we ignore
        // we notify of the user disconnection the userLeft signal
        emit userLeft(userid);
    }
}
//------------------------------------------------------------------------------------------
void ChatClient::connectToServer(const QHostAddress &address, uint port)
{
    m_clientSocket->connectToHost(address, port);
}
//------------------------------------------------------------------------------------------
void ChatClient::onReadyRead()
{
    // Prepare a container to hold the UTF-8 encoded JSON we receive from the socket
    QByteArray jsonData;
    // Create a QDataStream operating on the socket
    QDataStream socketStream(m_clientSocket);
    // Set the version so that programs compiled with different versions of Qt can agree on how to serialise
    socketStream.setVersion(QDataStream::Qt_5_7);
    // Start an infinite loop
    for (;;)
    {
        /* We start a transaction so we can revert to the previous state
         * in case we try to read more data than is available on the socket */
        socketStream.startTransaction();
        // We try to read the JSON data
        socketStream >> jsonData;
        if (socketStream.commitTransaction())
        {
            // We successfully read some data
            // We now need to make sure it's in fact a valid JSON
            QJsonParseError parseError;
            // We try to create a json document with the data we received
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
            if (parseError.error == QJsonParseError::NoError)
            {
                // If the data was indeed valid JSON
                if (jsonDoc.isObject()) // and is a JSON object
                    jsonReceived(jsonDoc.object()); // parse the JSON
            }
            // Loop and try to read more JSONs if they are available
        } else
        {
            /* The read failed, the socket goes automatically back to the state
             * it was in before the transaction started
             * we just exit the loop and wait for more data to become available */
            break;
        }
    }
}
