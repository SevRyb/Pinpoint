#include <QIntValidator>
#include "serversetupwindow.h"

ServerSetupWindow::ServerSetupWindow(QWidget *parent)
    : QWidget{parent}
{
    resize(400, 100);
    setWindowFlags(Qt::Dialog);
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(tr("Pinpoint - Server setup"));

    m_mainVBoxLay = new QVBoxLayout(this);
    setLayout(m_mainVBoxLay);

    m_ipLineEdit = new QLineEdit("127.0.0.1", this);
    m_ipLineEdit->setPlaceholderText(tr("IPv4 Adress"));
    m_ipLineEdit->setToolTip(tr("IPv4 Adress"));

    m_portLineEdit = new QLineEdit("1967", this);  // Default port is 1967
    QIntValidator *port_validator = new QIntValidator(0, 65535, this);
    m_portLineEdit->setValidator(port_validator);
    m_portLineEdit->setToolTip(tr("Port"));
    m_portLineEdit->setPlaceholderText(tr("Port"));

    m_joinButton = new QPushButton(this);

    m_mainVBoxLay->addWidget(m_ipLineEdit);
    m_mainVBoxLay->addWidget(m_portLineEdit);
    m_mainVBoxLay->addWidget(m_joinButton, 0, Qt::AlignHCenter);

    connect(m_joinButton, &QPushButton::clicked, this, &ServerSetupWindow::connectToServerBtn);
}
//------------------------------------------------------------------------------------------
void ServerSetupWindow::connectToServerBtn()
{
    if (m_isConnectedToServer)
    {
        m_ipLineEdit->setReadOnly(false);
        m_portLineEdit->setReadOnly(false);
        m_joinButton->setText(tr("Join"));
    }
    emit connectToServer(m_ipLineEdit->text(), m_portLineEdit->text().toUShort());
}
//------------------------------------------------------------------------------------------
void ServerSetupWindow::show(bool is_connected)
{
    if (is_connected)
    {
        m_isConnectedToServer = true;
        m_ipLineEdit->setReadOnly(true);
        m_portLineEdit->setReadOnly(true);
        m_joinButton->setText(tr("Leave"));
    } else
    {
        m_isConnectedToServer = false;
        m_ipLineEdit->setReadOnly(false);
        m_portLineEdit->setReadOnly(false);
        m_joinButton->setText(tr("Join"));
    }
    QWidget::show();
}
