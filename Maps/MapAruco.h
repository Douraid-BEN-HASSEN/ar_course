#ifndef MAPARUCO_H
#define MAPARUCO_H

#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>

#include <Kart/Map/Map.h>

class MapAruco: public Map
{
public:
    static MapAruco *instance();

    bool setMapInfo(cv::Mat &pImage);
private:
    MapAruco(QObject *parent = nullptr);
    ~MapAruco();
};

#endif // MAPARUCO_H
