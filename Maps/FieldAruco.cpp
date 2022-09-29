#include "FieldAruco.h"

FieldAruco *FieldAruco::instance() {
    static FieldAruco instance;
    return &instance;
}

// constructor
FieldAruco::FieldAruco(): Field{}
{

}

// destructor
FieldAruco::~FieldAruco()
{
}

bool FieldAruco::setMapInfo(cv::Mat &pImage)
{
    bool success = false;
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

    // get map bounds
    if (ids.size() > 0)
    {
        success = true;
        // On dessine les marqueurs détectés sur l'image
        cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);

        int itId = 0; // index pour parcourir le tableau d'ID

        // correspond aux cordonnées qui délimite la map
        cv::Point2f topleft(9999, 0);
        cv::Point2f bottomLeft(9999, 9999);
        cv::Point2f topRight(0, 0);
        cv::Point2f bottomRight(0, 9999);

        cv::Point2f itemPos(9999, 0); // correspond aux cordonnées d'un item (checkpoint ou obstacle)

        // remplissage tableau result
        for (std::vector<std::vector< cv::Point2f >>::iterator nCorner = corners.begin(); nCorner != corners.end(); nCorner++) {
            // reset pos
            itemPos.x = 9999;
            itemPos.y = 0;
            for (std::vector< cv::Point2f >::iterator nPoint = nCorner->begin(); nPoint != nCorner->end(); nPoint++) {
                if(ids[itId] < 10) {
                    // utile pour le calcul de maxHeight & maxWidth
                    if(nPoint->x < topleft.x) topleft.x = nPoint->x;
                    if(nPoint->y > topleft.y) topleft.y = nPoint->y;

                    if(nPoint->x < bottomLeft.x) bottomLeft.x = nPoint->x;
                    if(nPoint->y < bottomLeft.y) bottomLeft.y = nPoint->y;

                    if(nPoint->x > topRight.x) topRight.x = nPoint->x;
                    if(nPoint->y > topRight.y) topRight.y = nPoint->y;

                    if(nPoint->x > bottomRight.x) bottomRight.x = nPoint->x;
                    if(nPoint->y < bottomRight.y) bottomRight.y = nPoint->y;
                } else {
                    if(nPoint->x < itemPos.x) itemPos.x = nPoint->x;
                    if(nPoint->y > itemPos.y) itemPos.y = nPoint->y;
                }
            }

            if(ids[itId] > 9 && ids[itId] < 200) {
                Checkpoint *checkpoint = new Checkpoint();
                checkpoint->setId(ids[itId]);
                checkpoint->setX(itemPos.x);
                checkpoint->setY(itemPos.y);
                if(this->_checkpoints->contains(checkpoint->getId())) {
                    this->_checkpoints->remove(checkpoint->getId());
                    this->_checkpoints->insert(checkpoint->getId(), checkpoint);
                } else this->_checkpoints->insert(checkpoint->getId(), checkpoint);
            } else if(ids[itId] > 9 && ids[itId] < 250) {
                Obstacle *obstacle = new Obstacle();
                obstacle->setId(ids[itId]);
                obstacle->setX(itemPos.x);
                obstacle->setY(itemPos.y);
                obstacle->setAngle(0);
                if(this->_obstacles->contains(obstacle->getId())) {
                    this->_obstacles->remove(obstacle->getId());
                    this->_obstacles->insert(obstacle->getId(), obstacle);
                } else this->_obstacles->insert(obstacle->getId(), obstacle);
            }

            // === gestion des timeout ===
            bool contains;
            // liste contenant les ids à supprimer
            int timeoutLimit = 5000;
            QList<int> checkpointIdTimedout;
            QList<int> obstacleIdTimedout;

            // checkpoint
            foreach(Checkpoint *checkpoint, *this->_checkpoints) {
                contains = false;
                for(std::vector<int>::iterator id = ids.begin(); id != ids.end(); id++) {
                    contains = checkpoint->getId() == *id;
                    if(contains) {
                        checkpoint->setTimeout(0); // reset timeout
                        break;
                    }
                }
                if(!contains) checkpoint->setTimeout(checkpoint->getTimeout()+1);
                if(checkpoint->getId() >= timeoutLimit) checkpointIdTimedout.append(checkpoint->getId());
            }
            // obstacle
            foreach(Obstacle *obstacle, *this->_obstacles) {
                contains = false;
                for(std::vector<int>::iterator id = ids.begin(); id != ids.end(); id++) {
                    contains = obstacle->getId() == *id;
                    if(contains) {
                        obstacle->setTimeout(0); // reset timeout
                        break;
                    }
                }
                if(!contains) obstacle->setTimeout(obstacle->getTimeout()+1);
                if(obstacle->getId() >= timeoutLimit) obstacleIdTimedout.append(obstacle->getId());
            }

            // suppression des elements
            foreach (int id, checkpointIdTimedout) {
                this->_checkpoints->remove(id);
            }

            foreach (int id, obstacleIdTimedout) {
                this->_obstacles->remove(id);
            }
            // ============================

            itId++;
        }

        // enregistrement des limites map
        this->setMapWidth(topRight.x);
        this->setMapHeight(topRight.y);
    }

    //afficher la sortie
    cv::imshow("out", imageCopy);

    return success;
}
