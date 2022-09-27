#include <QCoreApplication>
#include "caruco.h"
#include "MqttService.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CAruco aruco;
    CMQtt mqtt(nullptr, "127.0.0.1", 1883, "", "");

    cv::VideoCapture inputVideo(4);
    cv::Mat image;

    QList<int> ids;

    while(true)
    {
        inputVideo.grab();
        inputVideo.retrieve(image);

        ids = aruco.detect(image);
        if(ids.count()>0) {
            for(int nId=0; nId<ids.count(); nId++)
                mqtt.publish("topic", QString::number(ids[nId]));
        }

        qDebug() << ids;

        cv::waitKey(20);
    }

    return a.exec();
}
