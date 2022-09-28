#ifndef FIELDARUCO_H
#define FIELDARUCO_H

#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>

#include "../../Tools/MqttExchanger/src/Kart/Map/Field.h"

class FieldAruco: public Field
{
public:
    static FieldAruco *instance();

    bool setMapInfo(cv::Mat &pImage);
private:
    FieldAruco();
    ~FieldAruco();
};

#endif // FIELDARUCO_H
