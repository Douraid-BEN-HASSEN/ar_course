#include <QApplication>

#include "Mqtt/MqttService.h"
#include "testQGraphics2022/widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MqttService::instance();

    Widget w;
    w.show();
    return a.exec();
}
