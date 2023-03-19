#include "animbutton.h"

AnimButton::AnimButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    init();
}
//------------------------------------------------------------------------------------------
AnimButton::AnimButton(QWidget *parent)
    : QPushButton(parent)
{
    init();
}
//------------------------------------------------------------------------------------------
void AnimButton::init()
{
    setStyleSheet("QPushButton {border: none; background: transparent;}");
    // Animations
    QEasingCurve curve;
    curve.setType(QEasingCurve::InExpo);
    m_pressAnimation = new QVariantAnimation(this);
    m_pressAnimation->setDuration(100);
    m_pressAnimation->setStartValue(QSize(35, 35));
    m_pressAnimation->setEndValue(QSize(25, 25));
    m_pressAnimation->setEasingCurve(curve);
    connect(m_pressAnimation, &QVariantAnimation::valueChanged, this, [this](const QVariant& var)
    {
        this->setIconSize(var.toSize());
    });
    m_releaseAnimation = new QVariantAnimation(this);
    m_releaseAnimation->setDuration(100);
    m_releaseAnimation->setStartValue(QSize(25, 25));
    m_releaseAnimation->setEndValue(QSize(35, 35));
    connect(m_releaseAnimation, &QVariantAnimation::valueChanged, this, [this](const QVariant& var)
    {
        this->setIconSize(var.toSize());
    });

    m_enterAnimation = new QVariantAnimation(this);
    m_enterAnimation->setDuration(150);
    m_enterAnimation->setStartValue(QSize(30, 30));
    m_enterAnimation->setEndValue(QSize(35, 35));
    connect(m_enterAnimation, &QVariantAnimation::valueChanged, this, [this](const QVariant& var)
    {
        this->setIconSize(var.toSize());
    });
    m_leaveAnimation = new QVariantAnimation(this);
    m_leaveAnimation->setDuration(150);
    m_leaveAnimation->setStartValue(QSize(35, 35));
    m_leaveAnimation->setEndValue(QSize(30, 30));
    connect(m_leaveAnimation, &QVariantAnimation::valueChanged, this, [this](const QVariant& var)
    {
        this->setIconSize(var.toSize());
    });
}
//------------------------------------------------------------------------------------------
void AnimButton::mouseReleaseEvent(QMouseEvent *event)
{
    m_releaseAnimation->start();
    QPushButton::mouseReleaseEvent(event);
}
//------------------------------------------------------------------------------------------
void AnimButton::mousePressEvent(QMouseEvent *event)
{
     m_pressAnimation->start();
     QPushButton::mousePressEvent(event);
}
//------------------------------------------------------------------------------------------
void AnimButton::enterEvent(QEvent *event)
{
    m_enterAnimation->start();
    QPushButton::enterEvent(event);
}
//------------------------------------------------------------------------------------------
void AnimButton::leaveEvent(QEvent *event)
{
    m_leaveAnimation->start();
    QPushButton::leaveEvent(event);
}
//------------------------------------------------------------------------------------------
