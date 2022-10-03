#ifndef MAPARUCO_H
#define MAPARUCO_H

#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>
#include <Kart/Map/Map.h>
#include <QPoint>
#include <QTimer>

class MapAruco: public Map
{
public:
    static MapAruco *getInstance();
    bool setMapInfo(cv::Mat &pImage);

    void publish();

private:
    MapAruco(QObject *parent = nullptr);
    ~MapAruco();

    int _timeoutLimit = 5000;
};

#endif // MAPARUCO_H
