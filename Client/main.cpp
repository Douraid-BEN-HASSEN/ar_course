#include <QApplication>

#include "testQGraphics2022/widget.h"
#include "Mqtt/MqttService.h"
#include "Kart/Map/Map.h"
#include "kart/Map/Checkpoint.h"
#include "Kart/Map/Obstacle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MqttService::instance();

    Map::instance();

    Checkpoint *c = new Checkpoint;
    Obstacle *o = new Obstacle;


    Widget w;
    w.show();
    return a.exec();
}
