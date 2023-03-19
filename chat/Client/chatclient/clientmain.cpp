#include <QApplication>
#include "chatwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(":/icons/icon-256.png"));
    QFontDatabase::addApplicationFont(":/fonts/seguiemj.ttf");
    QFontDatabase::addApplicationFont(":/fonts/OpenSans-VariableFont.ttf");
    ChatWindow Chat_Window;
    Chat_Window.show();
    return app.exec();
}
