#ifndef MAPARUCO_H
#define MAPARUCO_H

#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>
#include <Kart/Map/Map.h>
#include <QPoint>

class MapAruco: public Map
{
public:
    static MapAruco *instance();
    bool setMapInfo(cv::Mat &pImage);

private:
    MapAruco();
    ~MapAruco();

    int _timeoutLimit;

};

#endif // MAPARUCO_H
