#include "window.h"

#include "src/Mqtt/MqttService.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{

    MqttService* ptr1 = MqttService::instance();
    MqttService* ptr2 = MqttService::instance();

    qDebug() << ptr1 << " | " << ptr2 << Qt::endl;

    QApplication a(argc, argv);
    Window w;
    w.show();
    return a.exec();
}
