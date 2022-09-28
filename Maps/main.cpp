#include <QCoreApplication>
#include "MqttService.h"
#include "FieldAruco.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MqttService *mqtt = MqttService::instance();
    FieldAruco *map = FieldAruco::instance();

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
