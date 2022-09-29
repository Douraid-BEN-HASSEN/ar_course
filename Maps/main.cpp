#include <QCoreApplication>
#include <Mqtt/MqttService.h>
#include "MapAruco.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MqttService *mqtt = MqttService::instance();
    MapAruco *map = MapAruco::instance();

    cv::VideoCapture inputVideo(4);
    cv::Mat image;

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
