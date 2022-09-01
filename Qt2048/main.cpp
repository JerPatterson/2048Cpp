#include "Qt2048.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qt2048 w;
    w.show();
    return a.exec();
}
