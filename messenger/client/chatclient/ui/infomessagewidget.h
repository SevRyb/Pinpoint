#ifndef INFOMESSAGEWIDGET_H
#define INFOMESSAGEWIDGET_H

#include <QLabel>
#include <QVBoxLayout>
#include "messagewidget.h"

class InfoMessageWidget : public MessageWidget
{
    Q_OBJECT
public:
    explicit InfoMessageWidget(const QString &text = "", QWidget *parent = nullptr);
    void setText(const QString &text);
private:
    QVBoxLayout *m_vBoxLay;
    QLabel *m_infoLabel;
};

#endif // INFOMESSAGEWIDGET_H
