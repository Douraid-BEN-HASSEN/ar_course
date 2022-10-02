#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

#include <Mqtt/MqttService.h>

#include "MapAruco.h"

void publish_th();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MapAruco *mapAruco = MapAruco::getInstance();
    publish_th();

    cv::VideoCapture inputVideo(4);
    cv::Mat image;

    while(true)
    {
        inputVideo.grab();
        inputVideo.retrieve(image);
        mapAruco->setMapInfo(image);
        cv::waitKey(1);
    }

    return a.exec();
}

void publish_th() {
    QTimer::singleShot(1000, publish_th);
    QString result = MapAruco::getInstance()->serialize();
    MapAruco::getInstance()->publish();
}