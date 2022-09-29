#include <QCoreApplication>
#include <Kart/Player/GameMode.h>
#include <Mqtt/MqttService.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    GameMode game;

    MqttService *mqtt = MqttService::instance();

    return a.exec();
}
