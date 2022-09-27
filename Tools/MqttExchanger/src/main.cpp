#include "window.h"

#include "src/Mqtt/MqttService.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MqttService::instance();

    Window w;
    w.show();

    return a.exec();
}
