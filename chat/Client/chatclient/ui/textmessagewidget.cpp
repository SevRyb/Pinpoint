#include "textmessagewidget.h"

TextMessageWidget::TextMessageWidget(MessagePurpose msgPurpose, QWidget *parent)
    : MessageWidget(msgPurpose, parent)
    , m_parentWidget(parent)
{
    MessageWidget::m_msgType = MessageType::TEXT;

    m_vBoxLay = new QVBoxLayout(this);
    m_vBoxLay->setSizeConstraint(QLayout::SetMinAndMaxSize);
    m_vBoxLay->setContentsMargins(0, 0, 0, 0);
    m_vBoxLay->setSpacing(0);
    setLayout(m_vBoxLay);

    m_maxWidth = m_parentWidget->width() / 2; // test

    m_signatureLabel = new QLabel(this);
    m_signatureLabel->setStyleSheet(
                ".QLabel {"
                    "font-size: 10pt;"
                    "background: transparent;"
                "}");
    m_signatureLabel->setMaximumWidth(m_maxWidth);

    m_font.setFamily(":/fonts/seguiemj.ttf");
    m_font.setPixelSize(20);
    m_msgTextEdit = new QTextEdit(this);

    m_msgTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_msgTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_msgTextEdit->setFont(m_font);
    m_msgTextEdit->setFixedWidth(m_maxWidth);
    m_msgTextEdit->setReadOnly(true);

    setStyleSheet("QTextEdit"
                  "{"
                    "background: rgba(52, 69, 99, 200);"
                    "color: white;"
                    "font-family: Segoe UI Emoji;"
                    "border-radius: 10px;"
                    "padding: 5px 5px 5px 5px;"
                   "}");

    if (m_msgPurpose == MessagePurpose::INCOMING)
    {
        m_vBoxLay->addWidget(m_signatureLabel, 0, Qt::AlignLeft);
        m_vBoxLay->addWidget(m_msgTextEdit, 1, Qt::AlignLeft);
        m_msgTextEdit->setStyleSheet("QTextEdit"
                                     "{"
                                       "border-bottom-left-radius: 0px;"
                                     "}");
    }
    else if (m_msgPurpose == MessagePurpose::UPCOMING)
    {
        m_vBoxLay->addWidget(m_signatureLabel, 0, Qt::AlignRight);
        m_vBoxLay->addWidget(m_msgTextEdit, 1, Qt::AlignRight);
        m_msgTextEdit->setStyleSheet("QTextEdit"
                                     "{"
                                       "border-bottom-right-radius: 0px;"
                                     "}");
    }
}
//------------------------------------------------------------------------------------------
void TextMessageWidget::setText(const QString &time_sign, const QString &whose, const QString &text)
{
    if (text.length() == 1 || text.length() == 2)
    {
        m_msgTextEdit->setStyleSheet("QTextEdit "
                                     "{"
                                        "background: transparent;"
                                     "}");
        // If it's an emoji (we check UTF-32 code range)
        if (text.toUcs4().first() >= 0x1F600) // TODO: replace code
            m_font.setPixelSize(40);
        // It's an ordinary text
        else
        {
            m_font.setPixelSize(30);
            m_font.setBold(true);
        }
    }
    else
    {
        m_font.setPixelSize(20);
        m_font.setBold(false);
    }

    m_msgTextEdit->setFont(m_font);
    m_fontMetrics = new QFontMetrics(m_msgTextEdit->fontMetrics());

    const int padding = 8+6 + 2*2;  // TODO: get from QTextEdit (padding + 2*border_width)
    QRect fit_rect(0, 0, m_maxWidth - padding, m_fontMetrics->height());
    QRect text_rect = m_fontMetrics->boundingRect(fit_rect, Qt::TextWordWrap, text);

    m_msgTextEdit->setFixedSize(text_rect.width() + padding, text_rect.height() + padding);

    if (m_msgPurpose == MessagePurpose::INCOMING)
    {
        m_signatureLabel->setText(time_sign + " " + whose);
    }
    else if (m_msgPurpose == MessagePurpose::UPCOMING)
    {
        m_signatureLabel->setText(whose + " " + time_sign);
    }
    m_msgTextEdit->setText(text);
}
//------------------------------------------------------------------------------------------
void TextMessageWidget::onResize()
{
    //MessageWidget::resizeEvent(event);
    // TODO: Update widget size
    m_maxWidth = m_parentWidget->width() / 2; // test
    m_fontMetrics = new QFontMetrics(m_msgTextEdit->fontMetrics());

    const int padding = 8+6 + 2*2;  // TODO: get from QTextEdit (padding + 2*border_width)
    QRect fit_rect(0, 0, m_maxWidth - padding, m_fontMetrics->height());
    QRect text_rect = m_fontMetrics->boundingRect(fit_rect, Qt::TextWordWrap, m_msgTextEdit->toPlainText());

    m_msgTextEdit->setFixedSize(text_rect.width() + padding, text_rect.height() + padding);
}
