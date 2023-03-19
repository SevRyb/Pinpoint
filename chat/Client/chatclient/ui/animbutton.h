#ifndef ANIMBUTTON_H
#define ANIMBUTTON_H

#include <QPushButton>
#include <QVariantAnimation>

class AnimButton : public QPushButton
{
    Q_OBJECT
public:
    explicit AnimButton(const QString &text = "", QWidget *parent = nullptr);
    explicit AnimButton(QWidget *parent = nullptr);
protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
private:
    QVariantAnimation *m_pressAnimation;
    QVariantAnimation *m_releaseAnimation;
    QVariantAnimation *m_enterAnimation;
    QVariantAnimation *m_leaveAnimation;
    void init();
};

#endif // ANIMBUTTON_H
