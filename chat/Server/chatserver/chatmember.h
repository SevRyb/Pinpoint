#ifndef CHATMEMBER_H
#define CHATMEMBER_H

#include <QString>

class ChatMember
{
public:
    ChatMember(const QString &username = "", int id = 0);
    int id();
    QString username();
    void setId(int id);
    void setUsername(const QString &username);
private:
    QString m_username;
    int m_id;
};

#endif // CHATMEMBER_H
