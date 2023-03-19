#include "chatmember.h"

ChatMember::ChatMember(const QString &username, int id)
    : m_username{username}, m_id{id}
{
}
//------------------------------------------------------------------------------------------
int ChatMember::id()
{
    return m_id;
}
//------------------------------------------------------------------------------------------
QString ChatMember::username()
{
    return m_username;
}
//------------------------------------------------------------------------------------------
void ChatMember::setId(int id)
{
    m_id = id;
}
//------------------------------------------------------------------------------------------
void ChatMember::setUsername(const QString &username)
{
    m_username = username;
}
