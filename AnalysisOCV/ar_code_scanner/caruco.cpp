#include "caruco.h"

CAruco::CAruco()
{

}

QList<int> CAruco::detect(cv::Mat &pImage)
{
    QList<int> result;
    std::vector< std::vector< cv::Point2f > > corners, rejected;
    std::vector< std::vector< cv::Point2f > > corners_final, rejected_final;
    std::vector< cv::Vec3d > rvecs_final, tvecs_final;
    cv::Mat imageCopy,circuit,idimage;
    std::vector<int> ids,ids_final;
    std::vector<int> v_x;
    std::vector<int> v_y;

    cv::Mat cameraMatrix, distCoeffs;
    cv::Ptr<cv::aruco::DetectorParameters> detectorParams = cv::aruco::DetectorParameters::create();
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

    pImage.copyTo(imageCopy);

    // detecter et dessiner les marqueurs trouvés
    cv::aruco::detectMarkers(pImage, dictionary, corners, ids, detectorParams);

    if (ids.size() > 0)
    {
        // On dessine les marqueurs détectés sur l'image
        cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);

        // remplissage talbeau result
        for (std::vector<int>::iterator nId = ids.begin() ; nId != ids.end(); nId++)
            result.append(*nId);
    }

    //afficher la sortie
    cv::imshow("out", imageCopy);

    return result;
}
