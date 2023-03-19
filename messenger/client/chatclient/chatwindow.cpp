#include <QStandardItemModel>
#include <QInputDialog>
#include <QMessageBox>
#include <QHostAddress>
#include <QDateTime>
#include <QScrollBar>
#include <QPixmap>
#include <QIcon>
#include <QRandomGenerator>
#include <QFontDatabase>
#include "chatwindow.h"
#include "chatclient.h"
#include "chatmember.h"
#include "textmessage.h"
#include "serversetupwindow.h"
#include "profilewindow.h"
#include "chatmemberswindow.h"
#include "emojiwindow.h"
#include "ui/textmessagewidget.h"
#include "ui/infomessagewidget.h"
#include "ui/animbutton.h"
#include "ui/messagetextedit.h"

ChatWindow::ChatWindow(QWidget *parent)
    : QWidget(parent)
    , m_chatClient(new ChatClient(this))
    , m_isConnectedToServer(false)
    , m_isWatchingOlderMsgs(false)
    , m_unreadMessages(0)
{
    QRandomGenerator generator =  QRandomGenerator::securelySeeded();
    QString username = QString("user%1").arg(generator.bounded(100, 999));
    m_chatMember = new ChatMember(username);
    setupUi();

    // Connect the signals from the chat client to the slots in this ui
    connect(m_chatClient, &ChatClient::connected, this, &ChatWindow::connectedToServer);
    connect(m_chatClient, &ChatClient::loggedIn, this, &ChatWindow::loggedIn);
    connect(m_chatClient, &ChatClient::loginError, this, &ChatWindow::loginFailed);
    connect(m_chatClient, &ChatClient::messageReceived, this, &ChatWindow::messageReceived);
    connect(m_chatClient, &ChatClient::disconnected, this, &ChatWindow::disconnectedFromServer);
    connect(m_chatClient, &ChatClient::error, this, &ChatWindow::error);
    connect(m_chatClient, &ChatClient::userJoined, this, &ChatWindow::userJoined);
    connect(m_chatClient, &ChatClient::userLeft, this, &ChatWindow::userLeft);
    // Connect the click of the "send" button and the press of the enter while typing to the slot that sends the message
    connect(m_msgTextEdit, &MessageTextEdit::returnPressed, this, &ChatWindow::sendMessage);
    connect(m_sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(m_emojiButton, &QPushButton::clicked, this, &ChatWindow::openEmojiWindow);
    connect(m_serverButton, &QPushButton::clicked, this, &ChatWindow::openServerSetupWindow);
    connect(m_profileButton, &QPushButton::clicked, this, &ChatWindow::openProfileWindow);
    connect(m_clientsButton, &QPushButton::clicked, this, &ChatWindow::openChatMembersWindow);
    connect(m_unreadMessagesButton, &QPushButton::clicked, this, [this]()
    {
        m_messagesScrollArea->verticalScrollBar()->setValue(m_messagesScrollArea->verticalScrollBar()->maximum());
    });
    // Connect(m_msgTextEdit, &shortcut, this, &ChatWindow::sendMessage);
    connect(m_messagesScrollArea->verticalScrollBar(), &QScrollBar::rangeChanged, this, &ChatWindow::scrollRangeChanged);
    connect(m_messagesScrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, &ChatWindow::scrollValueChanged);
    connect(m_emojiWindow, &EmojiWindow::insertEmoji, this, &ChatWindow::insertEmoji);
    connect(m_serverSetupWindow, &ServerSetupWindow::connectToServer, this, &ChatWindow::attemptConnection);
    connect(m_profileWindow, &ProfileWindow::apply, this, &ChatWindow::changeProfileSetup);
}
//------------------------------------------------------------------------------------------
ChatWindow::~ChatWindow() {}
//------------------------------------------------------------------------------------------
void ChatWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    // Update position of manually placed widgets
    m_unreadMessagesButton->setGeometry(width() / 2 - 150 / 2, height() - 110 - 50, 150, 30);
}
//------------------------------------------------------------------------------------------
void ChatWindow::attemptConnection(const QString &address, quint16 port)
{
    // If client is not already connected to server
    if (!m_isConnectedToServer)
    {
        // If username is not empty and doesn't contain whitespaces we connect to server
        if (!m_chatMember->username().isEmpty() && !m_chatMember->username().contains(' '))
            m_chatClient->connectToServer(QHostAddress(address), port);
    }
    else
        disconnectFromServer();
}
//------------------------------------------------------------------------------------------
void ChatWindow::disconnectFromServer()
{
    m_chatClient->disconnectFromHost();
    m_isConnectedToServer = false;
}
//------------------------------------------------------------------------------------------
void ChatWindow::connectedToServer()
{
    // Close the opened dialog window
    m_serverSetupWindow->close();
    // Try to login with the given username
    attemptLogin();
}
//------------------------------------------------------------------------------------------
void ChatWindow::attemptLogin()
{
    // Use the client to attempt a log in with the given username
    m_chatClient->login(m_chatMember->username());
}
//------------------------------------------------------------------------------------------
void ChatWindow::loggedIn(const int id, const uint joined_time, const QVector<ChatMember *> chat_members)
{
    m_chatMembers = chat_members;
    m_isConnectedToServer = true;
    m_chatMember->setId(id);
    m_chatMember->setJoinedTime(joined_time);
    if (!m_chatMembersWindow->isHidden())
        m_chatMembersWindow->updateChatMembersList();
    const int members = m_chatMembers.size();
    if (members > 0)
        m_clientsButton->setText(tr("%1 Members").arg(members + 1));
    else
        m_clientsButton->setText(tr("1 Member"));
    // Change Window title
    setWindowTitle(tr("Pinpoint [ %1 ] - connected").arg(m_chatMember->username()));
    //m_sendButton->setEnabled(true);
}
//------------------------------------------------------------------------------------------
void ChatWindow::loginFailed(const StatusCode code)
{
    // The server rejected the login attempt
    if (code == StatusCode::DUPLICATE)
    {
        const QString input = QInputDialog::getText(this, tr("Duplicate username"), tr("Client with this username already exists"),
                                           QLineEdit::Normal, m_chatMember->username());
        // If the dialog is rejected or input string is Null we terminate the connection
        if (input.isNull())
        {
            disconnectFromServer();
            return;
        }
        m_chatMember->setUsername(input);
        // Allow the user to retry, execute the same slot as when just connected
        connectedToServer();
    }
}
//------------------------------------------------------------------------------------------
void ChatWindow::messageReceived(Message *message)
{
    // Extract message time to display it
    QDateTime msg_time = QDateTime::fromSecsSinceEpoch(message->time());
    // If user scrolled upper
    if (m_isWatchingOlderMsgs)
    {
        m_unreadMessages++;
        showUnreadMessagesButton();
    }
    // Create new widget for message content
    TextMessageWidget *text_msg_widget = new TextMessageWidget(MessagePurpose::INCOMING, this);
    text_msg_widget->setText(msg_time.toString("HH:mm"), message->senderUserName(), message->text());
    // Display message
    showMessage(text_msg_widget);
    // Store message widget in a QVector
    m_messageWidgets.append(text_msg_widget);
    // Store message content in a QVector
    m_messages.append(message);
}
//------------------------------------------------------------------------------------------
void ChatWindow::sendMessage()
{
    if (!m_isConnectedToServer)
    {
        openServerSetupWindow();
        return;
    }
    const QString text = m_msgTextEdit->toPlainText();
    if (!text.isEmpty())
    {
        // Getting current time
        QDateTime now_time = QDateTime::currentDateTime();
        // Create TextMessage object to store our message
        TextMessage *message = new TextMessage(MessageType::TEXT, now_time.toSecsSinceEpoch(),
                                               text, m_chatMember->username(), m_chatMember->id());
        // Store message content in a QVector
        m_messages.append(message);
        // We use the client to send the message that the user typed
        m_chatClient->sendMessage(message);
        // Create new widget for message content
        TextMessageWidget *text_msg_widget = new TextMessageWidget(MessagePurpose::UPCOMING, this);
        text_msg_widget->setText(now_time.toString("HH:mm"), m_chatMember->username(), text);
        // Display message
        showMessage(text_msg_widget);
        // Store message widget in a QVector
        m_messageWidgets.append(text_msg_widget);
        // Clear the content of the message editor
        m_msgTextEdit->clear();
    }
    // Set focus for the message editor to allow user immediately write new message
    m_msgTextEdit->setFocus();
}
//------------------------------------------------------------------------------------------
void ChatWindow::disconnectedFromServer()
{
    m_isConnectedToServer = false;
    // If the client loses connection to the server
    // Comunicate the event to the user via a message box
    QMessageBox::warning(this, tr("Disconnected"), tr("The host terminated the connection"));
    // Clear QVector of chat members
    m_chatMembers.clear();
    // If chat members window is hidden we don't update it
    if (!m_chatMembersWindow->isHidden())
        m_chatMembersWindow->updateChatMembersList();
    // Change text of the button and window title
    m_clientsButton->setText(tr("Members"));
    setWindowTitle(tr("Pinpoint - not connected"));
}
//------------------------------------------------------------------------------------------
void ChatWindow::userJoined(ChatMember *chat_member)
{
    // Add new chat memebr to QVector of chat members
    m_chatMembers.append(chat_member);

    InfoMessageWidget *info_msg_widget = new InfoMessageWidget(tr("%1 joined").arg(chat_member->username()), this);
    showMessage(info_msg_widget);
    m_messageWidgets.append(info_msg_widget);

    const int members = m_chatMembers.size();
    if (members > 0)
        m_clientsButton->setText(tr("%1 Members").arg(members + 1));
    else
        m_clientsButton->setText(tr("1 Member"));
    // If chat members window is hidden we don't update it
    if (!m_chatMembersWindow->isHidden())
        m_chatMembersWindow->updateChatMembersList();
}
//------------------------------------------------------------------------------------------
void ChatWindow::userLeft(const int id)
{
    QString username;
    // We have to find the user, which left the chat to delete it
    ChatMember *member_to_delete = nullptr;
    for (int i = 0; i < m_chatMembers.size(); i++)
        if (m_chatMembers.at(i)->id() == id)
        {
            username = m_chatMembers.at(i)->username();
            member_to_delete = m_chatMembers.at(i);
            m_chatMembers.removeAt(i);
        }
    delete member_to_delete;

    InfoMessageWidget *info_msg_widget = new InfoMessageWidget(tr("%1 left").arg(username), this);
    showMessage(info_msg_widget);
    m_messageWidgets.append(info_msg_widget);

    const int members = m_chatMembers.size();
    if (members > 0)
        m_clientsButton->setText(tr("%1 Members").arg(members + 1));
    else
        m_clientsButton->setText(tr("1 Member"));
    // If chat members window is hidden we don't update it
    if (!m_chatMembersWindow->isHidden())
        m_chatMembersWindow->updateChatMembersList();
}
//------------------------------------------------------------------------------------------
void ChatWindow::error(QAbstractSocket::SocketError socket_error)
{
    // Show a message to the user that informs of what kind of error occurred
    switch (socket_error)
    {
    case QAbstractSocket::RemoteHostClosedError:
    case QAbstractSocket::ProxyConnectionClosedError:
        return; // Handled by disconnectedFromServer
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The host refused the connection"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The proxy refused the connection"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the proxy"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the server"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::critical(this, tr("Error"), tr("You don't have permissions to execute this operation"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::critical(this, tr("Error"), tr("Too many connections opened"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::warning(this, tr("Error"), tr("Operation timed out"));
        return;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy timed out"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::critical(this, tr("Error"), tr("Unable to reach the network"));
        break;
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::critical(this, tr("Error"), tr("An unknown error occured"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::critical(this, tr("Error"), tr("Operation not supported"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::critical(this, tr("Error"), tr("Your proxy requires authentication"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy comunication failed"));
        break;
    case QAbstractSocket::TemporaryError:
    case QAbstractSocket::OperationError:
        QMessageBox::warning(this, tr("Error"), tr("Operation failed, please try again"));
        return;
    default:
        Q_UNREACHABLE();
    }
}
//------------------------------------------------------------------------------------------
void ChatWindow::scrollRangeChanged()
{
    // Scroll to bottom if user is not reading older messages
    if (!m_isWatchingOlderMsgs)
        m_messagesScrollArea->verticalScrollBar()->setValue(m_messagesScrollArea->verticalScrollBar()->maximum());

}
//------------------------------------------------------------------------------------------
void ChatWindow::scrollValueChanged()
{
    if (m_messagesScrollArea->verticalScrollBar()->value() == m_messagesScrollArea->verticalScrollBar()->maximum())
    {
        m_isWatchingOlderMsgs = false;
        m_unreadMessages = 0;
        m_unreadMessagesButton->hide();
    }
    else
        m_isWatchingOlderMsgs = true;
}
//------------------------------------------------------------------------------------------
void ChatWindow::showMessage(MessageWidget *msg_widget)
{
    if (msg_widget->messagePurpose() == MessagePurpose::INCOMING)
    {
        m_messagesScrollVBoxLay->addWidget(msg_widget, 0, Qt::AlignTop);
    }
    else if (msg_widget->messagePurpose() == MessagePurpose::UPCOMING)
    {
        m_messagesScrollVBoxLay->addWidget(msg_widget, 0, Qt::AlignTop | Qt::AlignRight);
    }
    else if (msg_widget->messagePurpose() == MessagePurpose::INFO)
    {
        m_messagesScrollVBoxLay->addWidget(msg_widget, 0, Qt::AlignTop | Qt::AlignCenter);
    }
}
//------------------------------------------------------------------------------------------
void ChatWindow::showUnreadMessagesButton()
{
    if (m_unreadMessages > 99)
        m_unreadMessagesButton->setText(tr("99+ New messages"));
    else if (m_unreadMessages == 1)
        m_unreadMessagesButton->setText(tr("1 New message"));
    else
        m_unreadMessagesButton->setText(tr("%1 New messages").arg(m_unreadMessages));
    m_unreadMessagesButton->show();
}
//------------------------------------------------------------------------------------------
void ChatWindow::openEmojiWindow()
{
    m_emojiWindow->show();
}
//------------------------------------------------------------------------------------------
void ChatWindow::openServerSetupWindow()
{
    m_serverSetupWindow->show(m_isConnectedToServer);
}
//------------------------------------------------------------------------------------------
void ChatWindow::openProfileWindow()
{
    m_profileWindow->show(m_chatMember->username());
}
//------------------------------------------------------------------------------------------
void ChatWindow::openChatMembersWindow()
{
    m_chatMembersWindow->updateChatMembersList();
    m_chatMembersWindow->show();
}
//------------------------------------------------------------------------------------------
void ChatWindow::changeProfileSetup(const QString &username)
{
    m_chatMember->setUsername(username);
    m_profileWindow->close();
}
//------------------------------------------------------------------------------------------
void ChatWindow::insertEmoji(const QString &emoji)
{
    m_msgTextEdit->setFocus();
    m_msgTextEdit->insertPlainText(emoji);
}
//------------------------------------------------------------------------------------------
void ChatWindow::setupUi()
{
    setWindowTitle(tr("Pinpoint - not connected"));
    resize(700, 750);

    // Main Area
    m_mainVBoxLay = new QVBoxLayout(this);
    m_mainVBoxLay->setSpacing(0);
    m_mainVBoxLay->setContentsMargins(0, 0, 0, 0);
    setLayout(m_mainVBoxLay);

    // Messages Area
    m_messagesAreaVBoxLay = new QVBoxLayout;
    m_messagesAreaVBoxLay->setMargin(0);
    m_messagesArea = new QLabel(this);
    m_messagesArea->setAlignment(Qt::AlignCenter);

    m_messagesArea->setPixmap(QPixmap(":/icons/icon-bt.png"));
    m_messagesArea->setLayout(m_messagesAreaVBoxLay);

    m_messagesScrollArea = new QScrollArea(this);
    m_messagesScrollArea->setAttribute(Qt::WA_TranslucentBackground);
    m_messagesScrollArea->setWidgetResizable(true);
    m_messagesAreaVBoxLay->addWidget(m_messagesScrollArea);

    m_messagesScrollVBoxLay = new QVBoxLayout;
    m_messagesScrollVBoxLay->setSizeConstraint(QLayout::SetMinimumSize);
    m_messagesScrollVBoxLay->setAlignment(Qt::AlignTop);
    m_messagesScrollContainer = new QWidget(this);
    m_messagesScrollContainer->setAttribute(Qt::WA_TranslucentBackground);
    m_messagesScrollContainer->setLayout(m_messagesScrollVBoxLay);

    m_messagesScrollArea->setWidget(m_messagesScrollContainer);

    // Message editing Area
    m_messageEditingHBoxLay = new QHBoxLayout;
    m_messageEditingArea = new QWidget(this);
    m_messageEditingArea->setStyleSheet("QWidget"
                                        "{"
                                            "background: rgb(9, 30, 66);"
                                        "}"
                                        "QPlainTextEdit"
                                        "{"
                                            "color: rgb(234, 235, 239);"
                                            "font-family: Segoe UI Emoji;"
                                            "font-size: 20px;"
                                            "border: none;"
                                            "border-bottom: 2px solid rgb(115, 123, 138);"
                                        "}"
                                        "QPlainTextEdit:focus"
                                        "{"
                                            "border-color: rgb(234, 235, 239);"
                                        "}"
                                        "QMenu"
                                        "{"
                                            "background: rgb(0, 16, 40);"
                                            "color: rgb(115, 123, 138);"
                                        "}"
                                        "QMenu::item:selected"
                                        "{"
                                            "background: rgb(37, 56, 88);"
                                            "color: rgb(115, 123, 138);"
                                        "}");
    m_messageEditingArea->setFixedHeight(80);
    m_messageEditingArea->setLayout(m_messageEditingHBoxLay);

    m_msgTextEdit = new MessageTextEdit(this);
    m_msgTextEdit->setPlaceholderText(tr("Write a message..."));

    m_sendButton = new AnimButton(this);
    m_sendButton->setFixedSize(QSize(40, 40));
    m_sendButton->setIconSize(QSize(30, 30));
    m_sendButton->setIcon(QIcon(":/icons/send-btn.png"));

    m_emojiButton = new AnimButton(this);
    m_emojiButton->setFixedSize(QSize(40, 40));
    m_emojiButton->setIconSize(QSize(30, 30));
    m_emojiButton->setIcon(QIcon(":/icons/emoji-btn.png"));

    // Status bar Area
    m_statusBarGridLay = new QGridLayout;
    m_statusBarGridLay->setSpacing(0);
    m_statusBarGridLay->setContentsMargins(0, 0, 0, 0);
    m_statusBarArea = new QWidget(this);
    m_statusBarArea->setStyleSheet(
                "QWidget {background: rgb(0, 16, 40);}"
                "QPushButton"
                "{"
                    "color: rgb(115, 123, 138);"
                    "font-size: 15px;"
                    "font-weight: 500;"
                    "border: none;"
                    "border-radius: 4px;"
                    "padding: 0;"
                "}"
                "QPushButton:hover"
                "{"
                    "background: rgb(7, 22, 44);"
                "}"
                "QFrame"
                "{"
                    "background: rgb(62, 74, 92);"
                "}");
    m_statusBarArea->setFixedHeight(30);
    m_statusBarArea->setLayout(m_statusBarGridLay);
    m_serverButton = new QPushButton(tr("Server"), this);
    m_serverButton->setIcon(QIcon(":/icons/connection-icon.png"));
    m_serverButton->setFixedWidth(150);
    m_profileButton = new QPushButton(tr("Profile"), this);
    m_profileButton->setIcon(QIcon(":/icons/profile-icon.png"));
    m_profileButton->setFixedWidth(150);
    m_clientsButton = new QPushButton(tr("Members"), this);
    m_clientsButton->setIcon(QIcon(":/icons/members-icon.png"));
    m_clientsButton->setFixedWidth(150);

    // Layouts
    m_messageEditingHBoxLay->addWidget(m_msgTextEdit);
    m_messageEditingHBoxLay->addWidget(m_sendButton);
    m_messageEditingHBoxLay->addWidget(m_emojiButton);

    m_statusBarGridLay->addWidget(m_serverButton, 0, 0);
    m_statusBarGridLay->addWidget(createSeparator(), 0, 1);
    m_statusBarGridLay->addWidget(m_profileButton, 0, 2);
    m_statusBarGridLay->addWidget(createSeparator(), 0, 3);
    m_statusBarGridLay->addWidget(m_clientsButton, 0, 4);

    m_mainVBoxLay->addWidget(m_messagesArea, 1);
    m_mainVBoxLay->addWidget(m_messageEditingArea);
    m_mainVBoxLay->addWidget(m_statusBarArea);

    /* ---- Hidden Windows ---- */
    // Emoji Window
    m_emojiWindow = new EmojiWindow;
    m_emojiWindow->hide();
    // Server Setup Window
    m_serverSetupWindow = new ServerSetupWindow(this);
    m_serverSetupWindow->hide();
    // Profile Window
    m_profileWindow = new ProfileWindow(this);
    m_profileWindow->hide();
    // Chat Members Window
    m_chatMembersWindow = new ChatMembersWindow(&m_chatMembers, m_chatMember, &m_isConnectedToServer, this);
    m_chatMembersWindow->hide();

    m_unreadMessagesButton = new QPushButton(this);
    m_unreadMessagesButton->setStyleSheet("QPushButton"
                                          "{"
                                            "background: rgba(0, 101, 255, 240);"
                                            "color: white;"
                                            "font-size: 15px;"
                                            "font-weight: 500;"
                                            "border-radius: 15px;"
                                            "padding: 0;"
                                          "}"
                                          "QPushButton:hover"
                                          "{"
                                            "background: rgb(0, 101, 255);"
                                            "color: white;"
                                            "border: none;"
                                            "border-radius: 15px;"
                                          "}");
    m_unreadMessagesButton->setGeometry(width() / 2 - 150 / 2, height() - 110 - 50, 150, 30);
    m_unreadMessagesButton->hide();

    // Styles
    setStyleSheet(
                /* QWidget */
                "QWidget"
                "{"
                    "background: rgba(37, 56, 88, 255);"
                    "color: rgba(125, 140, 165, 255);"
                    "font-family: Open Sans;"
                    "border: none;"
                "}"
                /* QLabel */
                "QLabel"
                "{"
                    "font-size: 18px;"
                "}"
                /* QPushButton */
                "QPushButton"
                "{"
                    "background: rgb(255, 81, 48);"
                    "color: white;"
                    "font-size: 20px;"
                    "font-weight: bold;"
                    "border-radius: 8px;"
                    "padding: 5px 20px 5px 20px;"
                "}"
                "QPushButton:pressed"
                "{"
                    "background: rgb(165, 83, 68);"
                "}"
                "QPushButton:hover"
                "{"
                    "border: 1px solid rgb(24, 43, 75);"
                    "padding: 0;"
                "}"
                /* QLineEdit */
                "QLineEdit"
                "{"
                    "background: rgb(24, 43, 75);"
                    "color: white;"
                    "border: 1px solid rgb(52, 71, 103);"
                    "border-radius: 6px;"
                    "font-size: 20px;"
                    "selection-background-color: rgb(52, 71, 103);"
                "}"
                "QLineEdit:disabled"
                "{"
                    "background: rgba(24, 43, 75, 50);"
                    "color: rgba(255, 255, 255, 50);"
                "}"
                "QLineEdit:read-only"
                "{"
                    "background: rgba(24, 43, 75, 50);"
                    "color: rgba(255, 255, 255, 50);"
                "}"
                /* Vertical QScrollBar */
                "QScrollBar:vertical"
                "{"
                    "background-color: rgba(0, 0, 0, 50);"
                    "border-radius: 3px;"
                    "width: 7px;"
                    "margin: 2px 0px 2px 0px;"
                "}"
                "QScrollBar::handle:vertical"
                "{"
                    "background-color: rgba(0, 0, 0, 140);"
                    "border-radius: 3px;"
                    "min-height: 20px;"
                    "max-height: 50px;"
                    "margin: 12px 0px 12px 0px;"
                "}"
                "QScrollBar::add-line:vertical"
                "{"
                    "background: transparent;"
                    "border-radius: 0px;"
                    "border-bottom-left-radius: 3px;"
                    "border-bottom-right-radius: 3px;"
                    "height: 10px;"
                "}"
                "QScrollBar::sub-line:vertical"
                "{"
                    "background: transparent;"
                    "border-radius: 0px;"
                    "border-top-left-radius: 3px;"
                    "border-top-right-radius: 3px;"
                    "height: 10px;"
                "}"
                "QScrollBar::up-arrow:vertical"
                "{"
                    "background: none;"
                "}"
                "QScrollBar::down-arrow:vertical"
                "{"
                    "background: none;"
                "}"
                "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical"
                "{"
                    "background: none;"
                "}"
                /* Horizontal QScrollBar */
                "QScrollBar:horizontal"
                "{"
                    "background-color: rgba(0, 0, 0, 50);"
                    "border-radius: 3px;"
                    "height: 7px;"
                    "margin: 0px 2px 0px 2px;"
                "}"
                "QScrollBar::handle:horizontal"
                "{"
                    "background-color: rgba(0, 0, 0, 140);"
                    "border-radius: 3px;"
                    "min-width: 20px;"
                    "max-width: 50px;"
                    "margin: 0px 12px 0px 12px;"
                "}"
                "QScrollBar::add-line:horizontal"
                "{"
                    "background: transparent;"
                    "border-radius: 0px;"
                    "border-bottom-left-radius: 3px;"
                    "border-bottom-right-radius: 3px;"
                    "width: 10px;"
                "}"
                "QScrollBar::sub-line:horizontal"
                "{"
                    "background: transparent;"
                    "border-radius: 0px;"
                    "border-top-left-radius: 3px;"
                    "border-top-right-radius: 3px;"
                    "width: 10px;"
                "}"
                "QScrollBar::up-arrow:horizontal"
                "{"
                    "background: none;"
                "}"
                "QScrollBar::down-arrow:horizontal"
                "{"
                    "background: none;"
                "}"
                "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal"
                "{"
                    "background: none;"
                "}"
                /* QMenu */
                "QMenu"
                "{"
                    "background: rgb(0, 16, 40);"
                    "color: rgb(115, 123, 138);"
                "}"
                "QMenu::item:selected"
                "{"
                    "background: rgb(37, 56, 88);"
                    "color: rgb(115, 123, 138);"
                "}");
}
//------------------------------------------------------------------------------------------
QFrame *ChatWindow::createSeparator()
{
    QFrame *separator = new QFrame(this);
    separator->setFixedSize(1, 17);
    return separator;
}
//------------------------------------------------------------------------------------------
