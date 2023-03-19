#include "textmessage.h"

TextMessage::TextMessage(MessageType type, uint time, const QString &text,
                         const QString &sender_username, int sender_id, int reply_id,
                         const QString &reply_text)
    : Message(type, time, sender_username, sender_id, reply_id)
    , m_text(text)
    , m_replyText(reply_text)
{}
//------------------------------------------------------------------------------------------
QString TextMessage::text() const
{
    return m_text;
}
//------------------------------------------------------------------------------------------
QString TextMessage::replyText() const
{
    return m_replyText;
}
//------------------------------------------------------------------------------------------
void TextMessage::setText(const QString &text)
{
    m_text = text;
}
//------------------------------------------------------------------------------------------
void TextMessage::setReplyText(const QString &reply_text)
{
    m_replyText = reply_text;
}
