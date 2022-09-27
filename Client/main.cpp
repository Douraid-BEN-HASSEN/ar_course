//#include "interface.h"
#include "testQGraphics2022/widget.h"
#include "testQGraphics2022/obstaclerect.h"

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
