#include <QCoreApplication>
#include "MqttService.h"
#include "../../Tools/MqttExchanger/src/Kart/Map/Field.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MqttService *mqtt = MqttService::instance();
    Field *map = Field::instance();

    cv::VideoCapture inputVideo(4);
    cv::Mat image;

    QList<int> ids;

    while(true)
    {
        inputVideo.grab();
        inputVideo.retrieve(image);

        map->setMapInfo(image);
        QString result = map->serialize();
        mqtt->publish("/map", result);

        cv::waitKey(1);
    }

    return a.exec();
}
