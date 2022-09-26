#include <QCoreApplication>
#include "caruco.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CAruco aruco;

    cv::VideoCapture inputVideo(0);
    cv::Mat image;

    while(true)
    {
        inputVideo.grab();
        inputVideo.retrieve(image);

        aruco.detect(image);

        cv::waitKey(20);
    }


    return a.exec();
}
