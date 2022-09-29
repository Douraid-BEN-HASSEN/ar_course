#include <QCoreApplication>
#include "mqttservice.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MqttService *mqtt = MqttService::instance();

    return a.exec();
}
