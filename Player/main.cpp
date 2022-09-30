#include "playerui.h"

#include <QApplication>
#include <Mqtt/MqttService.h>
#include <Kart/Game/Properties.h>

//class controlleur
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MqttService::instance();

    Properties::getInstance();

    //Class controleur pour gerer les interrupt
    PlayerUi w;
    w.show();
    return a.exec();
}
