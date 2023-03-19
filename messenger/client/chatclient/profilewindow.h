#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class ProfileWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ProfileWindow(QWidget *parent = nullptr);
    void show(const QString &username);
private:
    QVBoxLayout *m_mainVBoxLay;
    QLineEdit *m_usernameLineEdit;
    QPushButton *m_applyButton;
    void applyBtn();
signals:
    void apply(const QString &username);

};

#endif // PROFILEWINDOW_H
