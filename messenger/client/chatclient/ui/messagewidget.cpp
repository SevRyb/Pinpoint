#include <QDebug>
#include "messagewidget.h"

MessageWidget::MessageWidget(MessagePurpose msgPurpose, QWidget *parent)
    : QWidget{parent}
    , m_parentWidth(parent->width())
{
    m_msgPurpose = msgPurpose;
}
//------------------------------------------------------------------------------------------
MessageType MessageWidget::messageType()
{
    return m_msgType;
}
//------------------------------------------------------------------------------------------
MessagePurpose MessageWidget::messagePurpose()
{
    return m_msgPurpose;
}
//------------------------------------------------------------------------------------------
void MessageWidget::setMessagePurpose(MessagePurpose msgPurpose)
{
    m_msgPurpose = msgPurpose;
}
