#include <QCoreApplication>
#include <Mqtt/MqttService.h>
#include "MapAruco.h"
#include <QDebug>
#include <QTimer>

void publish_th();
const QString topicMap = "/map";

void publish_th() {
    QTimer::singleShot(1000, publish_th);
    QString result = MapAruco::instance()->serialize();
    MqttService::instance()->publish(topicMap, result);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MapAruco *mapAruco= MapAruco::instance();
    MqttService *mqtt = MqttService::instance();
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
