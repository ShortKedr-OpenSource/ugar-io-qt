#include "gamewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    GameWindow w;
    w.show();
    return app.exec();
}
