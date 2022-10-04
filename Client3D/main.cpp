#include <QGuiApplication>
#include "3DGraphics/Widget3D.h"


int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    Widget3D wd;

    wd.show();
    return app.exec();
}
