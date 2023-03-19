#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include "defines.h"

class MessageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MessageWidget(MessagePurpose msgPurpose, QWidget *parent = nullptr);
    MessageType messageType();
    MessagePurpose messagePurpose();
    void setMessagePurpose(MessagePurpose msgPurpose);
signals:

private:

protected:
    MessageType m_msgType;
    MessagePurpose m_msgPurpose;

    int m_parentWidth; // TODO: it has inherit this value
};

#endif // MESSAGEWIDGET_H
