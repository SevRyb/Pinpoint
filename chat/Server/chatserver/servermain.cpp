#include <QApplication>
#include "serverwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/icons/icon-256.png"));
    ServerWindow Server_Window;
    Server_Window.show();
    return a.exec();
}
