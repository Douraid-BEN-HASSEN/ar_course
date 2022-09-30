#include <QCoreApplication>

#include <Kart/Player/GameMode.h>

#include "Engine.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Engine engine;

    return a.exec();
}
