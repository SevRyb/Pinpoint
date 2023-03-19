#ifndef MESSAGETEXTEDIT_H
#define MESSAGETEXTEDIT_H

#include <QPlainTextEdit>

class MessageTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit MessageTextEdit(QWidget *parent = nullptr);
protected:
    virtual void keyPressEvent(QKeyEvent *event);
signals:
    void returnPressed();
};

#endif // MESSAGETEXTEDIT_H
