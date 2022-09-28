//#include "interface.h"
#include "Client2d/widget.h"
#include "Client2d/obstaclegraph.h"

#include <QApplication>
//#include <QtMqtt/QtMqtt>
#include <Mqtt/MqttService.h>

void init();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MqttService::instance();
    Widget ww;

    //w.show();
    ww.show();
    return a.exec();
}
