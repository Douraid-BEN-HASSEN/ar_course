#include <QCoreApplication>
#include <Kart/Player/GameMode.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    GameMode game;

    return a.exec();
}
