#ifndef CARUCO_H
#define CARUCO_H

#include <QList>
#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

//  +--------+
//  | CAruco |
//  +--------+
// classe qui permet de gérer l'identification des ARCode

class CAruco
{
public:
    CAruco();
    // Méthode qui retourne les ids dans une image
    QList<int> detect(cv::Mat &pImage);
};

#endif // CARUCO_H
