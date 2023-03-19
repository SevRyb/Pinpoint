#ifndef TEXTMESSAGEWIDGET_H
#define TEXTMESSAGEWIDGET_H

#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include "messagewidget.h"

class TextMessageWidget : public MessageWidget
{
    Q_OBJECT
public:
    explicit TextMessageWidget(MessagePurpose msgPurpose, QWidget *parent = nullptr);
    void setText(const QString &time_sign, const QString &whose, const QString &text);
    void onResize();
private:
    QFont m_font;
    QVBoxLayout *m_vBoxLay;
    QLabel *m_signatureLabel;
    QTextEdit *m_msgTextEdit;

    QFontMetrics* m_fontMetrics;

    int m_maxWidth;
    QWidget *m_parentWidget;
};

#endif // TEXTMESSAGEWIDGET_H
