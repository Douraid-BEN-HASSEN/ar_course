#include "client3dplayer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client3DPlayer w;
    w.show();
    return a.exec();
}
