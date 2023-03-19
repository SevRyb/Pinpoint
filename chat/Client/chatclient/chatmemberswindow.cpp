#include <QDateTime>
#include <QDebug>
#include "chatmemberswindow.h"

ChatMembersWindow::ChatMembersWindow(const QVector<ChatMember *> *chat_memebrs,
                                       const ChatMember *chat_member,
                                       const bool *is_connected,
                                       QWidget *parent)
    : QWidget{parent}
    , m_chatMemebrs(chat_memebrs)
    , m_chatMember(chat_member)
    , m_isConnectedToServer(is_connected)
{
    resize(300, 300);
    setWindowFlags(Qt::Tool);
    setWindowTitle(tr("Pinpoint - Members"));
    setStyleSheet("QWidget"
                  "{"
                    "background: rgba(37, 56, 88, 255);"
                  "}"
                  "QPushButton"
                  "{"
                    "background: rgb(24, 43, 75);"
                    "color: white;"
                    "font-size: 15px;"
                    "font-weight: 500;"
                    "border: 1px solid rgb(52, 71, 103);"
                    "border-radius: 6px;"
                    "padding: 0;"
                  "}");

    m_mainVBoxLay = new QVBoxLayout(this);
    m_mainVBoxLay->setContentsMargins(0, 0, 0, 0);
    setLayout(m_mainVBoxLay);

    m_scrollAreaVBoxLay = new QVBoxLayout;
    m_scrollAreaVBoxLay->setAlignment(Qt::AlignTop);

    m_scrollAreaContainer = new QWidget(this);
    m_scrollAreaContainer->setLayout(m_scrollAreaVBoxLay);

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setWidget(m_scrollAreaContainer);

    m_mainVBoxLay->addWidget(m_scrollArea);
    m_scrollAreaVBoxLay->addWidget(new QLabel(tr("Here is no memebrs..."), this), 1, Qt::AlignCenter);
}
//------------------------------------------------------------------------------------------
void ChatMembersWindow::updateChatMembersList()
{
    clearMembers();
    if (*m_isConnectedToServer)
    {
        QDateTime date_time;
        QPushButton *button;
        date_time = QDateTime::fromSecsSinceEpoch(m_chatMember->joinedTime());
        button = new QPushButton(tr("You - @%1 %2").arg(m_chatMember->username(), date_time.toString("HH:mm")), this);
        m_scrollAreaVBoxLay->addWidget(button, 0, Qt::AlignTop);
        for (ChatMember *chat_member : *m_chatMemebrs)
        {
            date_time = QDateTime::fromSecsSinceEpoch(chat_member->joinedTime());
            button = new QPushButton(tr("@%1 %2").arg(chat_member->username(), date_time.toString("HH:mm")), this);
            m_scrollAreaVBoxLay->addWidget(button, 0, Qt::AlignTop);
        }
        return;
    }
    m_label = new QLabel(tr("Here is no memebrs..."), this);
    m_scrollAreaVBoxLay->addWidget(m_label, 1, Qt::AlignCenter);
}
//------------------------------------------------------------------------------------------
void ChatMembersWindow::clearMembers()
{
    QLayoutItem *child;
    while ((child = m_scrollAreaVBoxLay->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child;
    }

}
