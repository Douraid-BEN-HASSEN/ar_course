#include <QApplication>

#include <Mqtt/MqttService.h>
#include <Kart/Map/Map.h>

#include "2DGraphics/widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MqttService::instance();

    Widget w;

    //Map *m = new Map();

    w.show();
    return a.exec();
}
