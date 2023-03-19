#include "infomessagewidget.h"

InfoMessageWidget::InfoMessageWidget(const QString &text, QWidget *parent)
    : MessageWidget(MessagePurpose::INFO, parent)
{
    MessageWidget::m_msgType = MessageType::TEXT;
    m_vBoxLay = new QVBoxLayout(this);
    setLayout(m_vBoxLay);

    m_infoLabel = new QLabel(text, this);

    m_vBoxLay->addWidget(m_infoLabel);

    m_infoLabel->setStyleSheet(
                ".QLabel "
                "{"
                    "font-size: 12pt;"
                    "background: transparent;"
                "}");
}
