#include "profilewindow.h"

ProfileWindow::ProfileWindow(QWidget *parent)
    : QWidget{parent}
{
    resize(400, 100);
    setWindowFlags(Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    setWindowTitle(tr("Pinpoint - Profile"));

    m_mainVBoxLay = new QVBoxLayout(this);
    setLayout(m_mainVBoxLay);

    m_usernameLineEdit = new QLineEdit(this);
    m_usernameLineEdit->setPlaceholderText(tr("Username"));
    m_usernameLineEdit->setToolTip(tr("Your username\nUsername couldn't be empty or include whitespaces"));

    m_applyButton = new QPushButton(tr("Apply"), this);

    m_mainVBoxLay->addWidget(m_usernameLineEdit);
    m_mainVBoxLay->addWidget(m_applyButton, 0, Qt::AlignHCenter);

    connect(m_applyButton, &QPushButton::clicked, this, &ProfileWindow::applyBtn);
}
//------------------------------------------------------------------------------------------
void ProfileWindow::applyBtn()
{
    const QString username = m_usernameLineEdit->text().trimmed();
    if (!username.isEmpty() && !username.contains(" "))
        emit apply(username);
}
//------------------------------------------------------------------------------------------
void ProfileWindow::show(const QString &username)
{
    m_usernameLineEdit->setText(username);
    QWidget::show();
}
