#include <QMessageBox>
#include "serverwindow.h"
#include "chatserver.h"

ServerWindow::ServerWindow(QWidget *parent)
    : QWidget(parent)
    , m_chatServer(new ChatServer(this))
{
    setupUi();
    connect(m_startStopButton, &QPushButton::clicked, this, &ServerWindow::toggleStartServer);
    connect(m_chatServer, &ChatServer::logMessage, this, &ServerWindow::logMessage);
}
//------------------------------------------------------------------------------------------
ServerWindow::~ServerWindow() {}
//------------------------------------------------------------------------------------------
void ServerWindow::toggleStartServer()
{
    // Check if the server is already listening connections
    if (m_chatServer->isListening())
    {
        m_chatServer->stopServer();  // Stop the server
        m_startStopButton->setText(tr("Start Server"));  // Change button title
        logMessage(QStringLiteral("Server Stopped"));  // Log server state
    } else
    {
        // Start listening connections
        // If the port is already in use
        if (!m_chatServer->listen(QHostAddress::Any, 1967))
        {
            QMessageBox::critical(this, tr("Error"), tr("Unable to start the server"));  // Show message box
            return;
        }
        logMessage(QStringLiteral("Server Started"));  // Log server state
        m_startStopButton->setText(tr("Stop Server"));  // Change button title
    }
}
//------------------------------------------------------------------------------------------
void ServerWindow::logMessage(const QString &msg)
{
    m_logEditor->appendPlainText(msg + QLatin1Char('\n'));
}
//------------------------------------------------------------------------------------------
void ServerWindow::setupUi()
{
    setWindowTitle("Pinpoint Server");
    resize(500, 500);
    m_logEditor = new QPlainTextEdit(this);
    m_startStopButton = new QPushButton(tr("Start Server"), this);
    m_vBoxLay = new QVBoxLayout(this);

    m_vBoxLay->addWidget(m_logEditor);
    m_vBoxLay->addWidget(m_startStopButton);

    setLayout(m_vBoxLay);

    m_logEditor->setReadOnly(true);

    // Styles
    setStyleSheet(
                /* QWidget */
                "QWidget"
                "{"
                    "background: rgba(37, 56, 88, 255);"
                    "color: rgba(125, 140, 165, 255);"
                "}"
                /* QLabel */
                "QLabel"
                "{"
                    "font-size: 18px;"
                "}"
                /* QPushButton */
                "QPushButton"
                "{"
                    "background: rgb(255, 81, 48);"
                    "color: white;"
                    "font-size: 20px;"
                    "font-weight: bold;"
                    "border-radius: 8px;"
                    "padding: 5px 10px;"
                "}"
                "QPushButton:pressed"
                "{"
                    "background: rgb(165, 83, 68);"
                "}"
                "QPushButton:hover"
                "{"
                    "border: 1px solid rgb(24, 43, 75);"
                    "padding: 5px 10px;"
                "}"
                /* QPlainTextEdit */
                "QPlainTextEdit"
                "{"
                    "background: rgba(24, 43, 75, 255);"
                    "color: white;"
                    "border: 1px solid rgb(52, 71, 103);"
                    "border-radius: 6px;"
                    "font-size: 12px;"
                    "selection-background-color: rgb(52, 71, 103);"
                    "padding: 0px 4px 0px 0px;"
                "}"
                /* Vertical QScrollBar */
                "QScrollBar:vertical"
                "{"
                    "background-color: rgba(0, 0, 0, 50);"
                    "border-radius: 3px;"
                    "width: 7px;"
                    "margin: 2px 0px 2px 0px;"
                "}"
                "QScrollBar::handle:vertical"
                "{"
                    "background-color: rgba(0, 0, 0, 40);"
                    "border-radius: 3px;"
                    "min-height: 20px;"
                    "max-height: 50px;"
                    "margin: 12px 0px 12px 0px;"
                "}"
                "QScrollBar::add-line:vertical"
                "{"
                    "background: transparent;"
                    "border-radius: 0px;"
                    "border-bottom-left-radius: 3px;"
                    "border-bottom-right-radius: 3px;"
                    "height: 10px;"
                "}"
                "QScrollBar::sub-line:vertical"
                "{"
                    "background: transparent;"
                    "border-radius: 0px;"
                    "border-top-left-radius: 3px;"
                    "border-top-right-radius: 3px;"
                    "height: 10px;"
                "}"
                "QScrollBar::up-arrow:vertical"
                "{"
                    "background: none;"
                "}"
                "QScrollBar::down-arrow:vertical"
                "{"
                    "background: none;"
                "}"
                "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical"
                "{"
                    "background: none;"
                "}"
                /* Horizontal QScrollBar */
                "QScrollBar:horizontal"
                "{"
                    "background-color: rgba(0, 0, 0, 50);"
                    "border-radius: 3px;"
                    "height: 7px;"
                    "margin: 0px 2px 0px 2px;"
                "}"
                "QScrollBar::handle:horizontal"
                "{"
                    "background-color: rgba(0, 0, 0, 140);"
                    "border-radius: 3px;"
                    "min-width: 20px;"
                    "max-width: 50px;"
                    "margin: 0px 12px 0px 12px;"
                "}"
                "QScrollBar::add-line:horizontal"
                "{"
                    "background: transparent;"
                    "border-radius: 0px;"
                    "border-bottom-left-radius: 3px;"
                    "border-bottom-right-radius: 3px;"
                    "width: 10px;"
                "}"
                "QScrollBar::sub-line:horizontal"
                "{"
                    "background: transparent;"
                    "border-radius: 0px;"
                    "border-top-left-radius: 3px;"
                    "border-top-right-radius: 3px;"
                    "width: 10px;"
                "}"
                "QScrollBar::up-arrow:horizontal"
                "{"
                    "background: none;"
                "}"
                "QScrollBar::down-arrow:horizontal"
                "{"
                    "background: none;"
                "}"
                "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal"
                "{"
                    "background: none;"
                "}"
                /* QMenu */
                "QMenu"
                "{"
                    "background: rgb(0, 16, 40);"
                    "color: rgb(115, 123, 138);"
                "}"
                "QMenu::item:selected"
                "{"
                    "background: rgb(37, 56, 88);"
                    "color: rgb(115, 123, 138);"
                "}");
}
