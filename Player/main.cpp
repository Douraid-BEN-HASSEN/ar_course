#include "playerui.h"

#include <QApplication>
#include "MqttService.h"

//class controlleur
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MqttService::instance();
    //Class controleur pour gerer les interrupt
    PlayerUi w;
    w.show();
    return a.exec();
}
