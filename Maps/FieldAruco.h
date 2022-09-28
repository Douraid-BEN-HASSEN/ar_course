#ifndef FIELDARUCO_H
#define FIELDARUCO_H

#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>

#include <Kart/Map/Map.h>

class FieldAruco: public Map
{
public:
    static FieldAruco *instance();

    bool setMapInfo(cv::Mat &pImage);
private:
    FieldAruco();
    ~FieldAruco();
};

#endif // FIELDARUCO_H
