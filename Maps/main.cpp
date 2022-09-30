#include <QCoreApplication>
#include "MqttService.h"
#include "MapAruco.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MqttService *mqtt = MqttService::instance();
    MapAruco *map = MapAruco::getInstance();

    cv::VideoCapture inputVideo(4);
    cv::Mat image;

    while(true)
    {
        inputVideo.grab();
        inputVideo.retrieve(image);

        map->publish();

        cv::waitKey(1);
    }

    return a.exec();
}
