#include "Qt2048.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Qt2048 window;
    window.show();

    return app.exec();
}
