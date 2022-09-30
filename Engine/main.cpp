#include <QApplication>

#include <Kart/Player/GameMode.h>
#include "Engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Engine engine;

    return a.exec();
}
