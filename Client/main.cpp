#include "interface.h"
#include <QApplication>
#include <QtMqtt/QtMqtt>

void init();

int main(int argc, char *argv[])
{
    init();

    QApplication a(argc, argv);
    interface w;
    w.show();
    return a.exec();
}

void init()
{
    auto client = new QMqttClient();
    client->setHostname("127.0.0.1");
    client->setPort(1887);
}
