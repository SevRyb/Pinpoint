#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QVector>
#include "defines.h"

class QHostAddress;
class QJsonDocument;
class TextMessage;
class Message;
class ChatMember;
class ChatClient : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatClient)
public:
    explicit ChatClient(QObject *parent = nullptr);
public slots:
    void connectToServer(const QHostAddress &address, uint port);
    void login(const QString &userName);
    void sendMessage(TextMessage *text_message);
    void disconnectFromHost();
private slots:
    void onReadyRead();
signals:
    void connected();
    void loggedIn(const int id, const uint joined_time, const QVector<ChatMember*> chat_members);
    void loginError(const StatusCode code);
    void disconnected();
    void messageReceived(Message *text_message);
    void error(QAbstractSocket::SocketError socketError);
    void userJoined(ChatMember *chat_member);
    void userLeft(const int id);
private:
    QTcpSocket *m_clientSocket;
    bool m_loggedIn;
    void jsonReceived(const QJsonObject &doc);
    TextMessage *m_currentTextMessage;
};

#endif // CHATCLIENT_H
