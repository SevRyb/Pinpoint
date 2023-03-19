#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include "message.h"

class TextMessage : public Message
{
public:
    TextMessage(MessageType type, uint time,
                 const QString &text, const QString &sender_username,
                 int sender_id, int reply_id = 0,
                 const QString &reply_text = QString());
    QString text() const;
    QString replyText() const;
    void setText(const QString &text);
    void setReplyText(const QString &reply_text);
protected:
    QString m_text;
    QString m_replyText;
};

#endif // TEXTMESSAGE_H
