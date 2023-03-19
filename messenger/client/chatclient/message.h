#ifndef MESSAGE_H
#define MESSAGE_H

#include <QVector>
#include <QString>
#include "defines.h"

class Message
{
public:
    Message(MessageType type, uint time,
             const QString &sender_username,
             int sender_id = 0, int reply_id = 0);

    MessageType type() const;
    uint time() const;
    int id() const;
    QString senderUserName() const;
    int senderId() const;
    //QVector<int> remindListIds() const;
    int replyId() const;

    void setType(const MessageType type);
    void setId(const int id);
    void setSenderUserName(const QString &username);
    void setSenderId(const int sender_id);
    void setReplyId(const int reply_id);
    //void setReamindListIds();

    virtual QString text() const = 0;
    virtual QString replyText() const = 0;
    virtual void setText(const QString &text) = 0;
    virtual void setReplyText(const QString &text) = 0;

protected:
    MessageType m_type;
    uint m_time;
    int m_id;
    int m_senderId;
    QString m_senderUserName;
    int m_replyId; // message id on which replied
    //QVector<int> m_remindListIds; // array of user id's
};

#endif // MESSAGE_H
