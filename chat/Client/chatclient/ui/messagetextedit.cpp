#include "messagetextedit.h"

MessageTextEdit::MessageTextEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{}
//------------------------------------------------------------------------------------------
void MessageTextEdit::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Return) & !(event->modifiers() == Qt::ShiftModifier))
    {
        emit returnPressed();
        QPlainTextEdit::keyPressEvent(event);
        clear();
        return;
    }
    QPlainTextEdit::keyPressEvent(event);
}
