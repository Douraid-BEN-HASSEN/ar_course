#include "playerui.h"

#include <QApplication>
#include "MqttService.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MqttService::instance();
    PlayerUi w;
    w.show();
    return a.exec();
}
