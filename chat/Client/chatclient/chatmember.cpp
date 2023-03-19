#include "chatmember.h"

ChatMember::ChatMember(const QString &username, const int id, const uint joined_time)
    : m_username(username)
    , m_id(id)
    , m_joinedTime(joined_time)
{
}
//------------------------------------------------------------------------------------------
int ChatMember::id() const
{
    return m_id;
}
//------------------------------------------------------------------------------------------
QString ChatMember::username() const
{
    return m_username;
}
//------------------------------------------------------------------------------------------
uint ChatMember::joinedTime() const
{
    return m_joinedTime;
}
//------------------------------------------------------------------------------------------
void ChatMember::setId(const int id)
{
    m_id = id;
}
//------------------------------------------------------------------------------------------
void ChatMember::setUsername(const QString &username)
{
    m_username = username;
}
//------------------------------------------------------------------------------------------
void ChatMember::setJoinedTime(const uint time)
{
    m_joinedTime = time;
}
