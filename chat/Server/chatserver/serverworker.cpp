#include <QDataStream>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include "serverworker.h"

ServerWorker::ServerWorker(QObject *parent)
    : QObject(parent)
    , m_serverSocket(new QTcpSocket(this))
    , m_id(0)
    , m_joinedTime(0)
{
    // Connect readyRead() to the slot that will take care of reading the data in
    connect(m_serverSocket, &QTcpSocket::readyRead, this, &ServerWorker::receiveJson);
    // Forward the disconnected and error signals coming from the socket
    connect(m_serverSocket, &QTcpSocket::disconnected, this, &ServerWorker::disconnectedFromClient);
    connect(m_serverSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ServerWorker::error);
}
//------------------------------------------------------------------------------------------м
bool ServerWorker::setSocketDescriptor(qintptr socketDescriptor)
{
    return m_serverSocket->setSocketDescriptor(socketDescriptor);
}
//------------------------------------------------------------------------------------------
void ServerWorker::sendJson(const QJsonObject &json)
{
    // We crate a temporary QJsonDocument forom the object and then convert it
    // to its UTF-8 encoded version. We use QJsonDocument::Compact to save bandwidth
    const QByteArray jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);
    // We notify the central server we are about to send the message
    emit logMessage(QLatin1String("Sending to ") + userName() + QLatin1String(" - ") + QString::fromUtf8(jsonData));
    // We send the message to the socket in the exact same way we did in the client
    QDataStream socketStream(m_serverSocket);
    socketStream.setVersion(QDataStream::Qt_5_7);
    socketStream << jsonData;
}
//------------------------------------------------------------------------------------------
void ServerWorker::disconnectFromClient()
{
    m_serverSocket->disconnectFromHost();
}
//------------------------------------------------------------------------------------------
QString ServerWorker::userName() const
{
    return m_userName;
}
//------------------------------------------------------------------------------------------
int ServerWorker::id()
{
    return m_id;
}
//------------------------------------------------------------------------------------------
uint ServerWorker::joinedTime() const
{
    return m_joinedTime;
}
//------------------------------------------------------------------------------------------
void ServerWorker::setUserName(const QString &userName)
{
    m_userName = userName;
}
//------------------------------------------------------------------------------------------
void ServerWorker::setId(int id)
{
    m_id = id;
}
//------------------------------------------------------------------------------------------
void ServerWorker::setJoinedTime(const uint time)
{
    m_joinedTime = time;
}
//------------------------------------------------------------------------------------------
void ServerWorker::receiveJson()
{
    // Prepare a container to hold the UTF-8 encoded JSON we receive from the socket
    QByteArray jsonData;
    // Create a QDataStream operating on the socket
    QDataStream socketStream(m_serverSocket);
    // Set the version so that programs compiled with different versions of Qt can agree on how to serialise
    socketStream.setVersion(QDataStream::Qt_5_7);
    // Start an infinite loop
    for (;;)
    {
        // Se start a transaction so we can revert to the previous state in case we try to read more data than is available on the socket
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
                    emit jsonReceived(jsonDoc.object()); // send the message to the central server
                else
                    emit logMessage(QLatin1String("Invalid message: ") + QString::fromUtf8(jsonData)); //notify the server of invalid data
            } else
            {
                emit logMessage(QLatin1String("Invalid message: ") + QString::fromUtf8(jsonData)); //notify the server of invalid data
            }
             // Loop and try to read more JSONs if they are available
        } else
        {
            /* The read failed, the socket goes automatically back
             * to the state it was in before the transaction started
             * We just exit the loop and wait for more data to become available */
            break;
        }
    }
}


