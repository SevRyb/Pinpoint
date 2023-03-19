#ifndef CHATMEMBERSWINDOW_H
#define CHATMEMBERSWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QVector>
#include "chatmember.h"

class ChatMembersWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ChatMembersWindow(const QVector<ChatMember*> *chat_memebrs,
                                  const ChatMember *chat_member,
                                  const bool *is_connected,
                                  QWidget *parent = nullptr);
    void updateChatMembersList();
    void clearMembers();
private:
    QVBoxLayout *m_mainVBoxLay;
    QScrollArea *m_scrollArea;
    QVBoxLayout *m_scrollAreaVBoxLay;
    QWidget *m_scrollAreaContainer;
    QLabel *m_label;
    const QVector<ChatMember *> *m_chatMemebrs;
    const ChatMember *m_chatMember;
    const bool *m_isConnectedToServer;
signals:

};

#endif // CHATMEMBERSWINDOW_H
