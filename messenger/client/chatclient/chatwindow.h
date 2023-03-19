#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QAbstractSocket>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QListView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QFrame>
#include <QVariantAnimation>
#include "defines.h"


class MessageWidget;
class AnimButton;
class MessageTextEdit;
class ServerSetupWindow;
class ProfileWindow;
class ChatMembersWindow;
class EmojiWindow;
class ChatClient;
class ChatMember;
class Message;
class ChatWindow : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatWindow)
public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
private:
    ChatClient *m_chatClient;
    ChatMember *m_chatMember;

    bool m_isConnectedToServer;
    bool m_isWatchingOlderMsgs;
    int m_unreadMessages;

    QVector<ChatMember*> m_chatMembers;
    QVector<Message*> m_messages;

    /* UI */
    // Main Area
    QVBoxLayout *m_mainVBoxLay;

    // Messages Area
    QLabel *m_messagesArea;
    QVBoxLayout *m_messagesAreaVBoxLay;

    QScrollArea *m_messagesScrollArea;

    QWidget *m_messagesScrollContainer;
    QVBoxLayout *m_messagesScrollVBoxLay;

    // Message editing Area
    QWidget *m_messageEditingArea;
    QHBoxLayout *m_messageEditingHBoxLay;

    MessageTextEdit *m_msgTextEdit;
    AnimButton *m_sendButton;
    AnimButton *m_emojiButton;

    // Status bar Area
    QWidget *m_statusBarArea;
    QGridLayout *m_statusBarGridLay;

    QPushButton *m_serverButton;
    QPushButton *m_clientsButton;
    QPushButton *m_profileButton;

    QVector<MessageWidget*> m_messageWidgets;

    QPushButton *m_unreadMessagesButton;

    // Windows
    ServerSetupWindow *m_serverSetupWindow;
    ProfileWindow *m_profileWindow;
    ChatMembersWindow *m_chatMembersWindow;
    EmojiWindow *m_emojiWindow;

    QFrame *createSeparator();
    void setupUi();
    void showMessage(MessageWidget *msg_widget);
    void showUnreadMessagesButton();
    void disconnectFromServer();
protected:
    virtual void resizeEvent(QResizeEvent *event);
private slots:
    void attemptConnection(const QString &address, quint16 port);
    void connectedToServer();
    void attemptLogin();
    void loggedIn(const int id, const uint joined_time, const QVector<ChatMember *> chat_members);
    void loginFailed(const StatusCode code);
    void messageReceived(Message *message);
    void sendMessage();
    void disconnectedFromServer();
    void userJoined(ChatMember *chat_member);
    void userLeft(const int id);
    void error(QAbstractSocket::SocketError socketError);
    void scrollRangeChanged();
    void scrollValueChanged();

    void openEmojiWindow();
    void openServerSetupWindow();
    void openProfileWindow();
    void openChatMembersWindow();

    void changeProfileSetup(const QString &username);
    void insertEmoji(const QString &emoji);
};

#endif // CHATWINDOW_H
