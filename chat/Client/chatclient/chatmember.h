#ifndef CHATMEMBER_H
#define CHATMEMBER_H

#include <QString>

class ChatMember
{
public:
    ChatMember(const QString &username = QString(), const int id = 0, const uint joined_time = 0);
    int id() const;
    QString username() const;
    uint joinedTime() const;

    void setId(const int id);
    void setUsername(const QString &username);
    void setJoinedTime(const uint time);
private:
    QString m_username;
    int m_id;
    uint m_joinedTime;
};

#endif // CHATMEMBER_H
