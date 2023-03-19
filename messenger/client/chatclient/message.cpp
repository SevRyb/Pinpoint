#include "message.h"

Message::Message(MessageType type, uint time, const QString &sender_username, int sender_id, int reply_id)
    : m_type(type)
    , m_time(time)
    , m_senderId(sender_id)
    , m_senderUserName(sender_username)
    , m_replyId(reply_id)
{
}
//------------------------------------------------------------------------------------------
MessageType Message::type() const
{
    return m_type;
}
//------------------------------------------------------------------------------------------
uint Message::time() const
{
    return m_time;
}
//------------------------------------------------------------------------------------------
int Message::id() const
{
    return m_id;
}
//------------------------------------------------------------------------------------------
QString Message::senderUserName() const
{
    return m_senderUserName;
}
//------------------------------------------------------------------------------------------
int Message::senderId() const
{
    return m_senderId;
}
//------------------------------------------------------------------------------------------
int Message::replyId() const
{
    return m_replyId;
}
//------------------------------------------------------------------------------------------
void Message::setType(const MessageType type)
{
    m_type = type;
}
//------------------------------------------------------------------------------------------
void Message::setId(const int id)
{
    m_id = id;
}
//------------------------------------------------------------------------------------------
void Message::setSenderUserName(const QString &username)
{
    m_senderUserName = username;
}
//------------------------------------------------------------------------------------------
void Message::setSenderId(const int sender_id)
{
    m_senderId = sender_id;
}
//------------------------------------------------------------------------------------------
void Message::setReplyId(const int reply_id)
{
    m_replyId = reply_id;
}
