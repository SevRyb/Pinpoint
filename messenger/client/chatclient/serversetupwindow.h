#ifndef SERVERSETUPWINDOW_H
#define SERVERSETUPWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class ServerSetupWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ServerSetupWindow(QWidget *parent = nullptr);
    void show(bool is_connected);
private:
    QVBoxLayout *m_mainVBoxLay;
    QLineEdit *m_ipLineEdit;
    QLineEdit *m_portLineEdit;
    QPushButton *m_joinButton;
    bool m_isConnectedToServer;
    void connectToServerBtn();
signals:
    void connectToServer(const QString &address, quint16 port);
};

#endif // SERVERSETUPWINDOW_H
