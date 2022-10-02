#include "window.h"
#include "2DGraphics/MapWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Window w;
    w.show();
    return a.exec();
}
