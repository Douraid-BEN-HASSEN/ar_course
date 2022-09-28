#include "Field.h"

Field *Field::instance() {
    static Field instance;
    return &instance;
}

// constructor
Field::Field(QObject *parent): QObject{parent}
{
    this->_mapWidth = -1;
    this->_mapHeight = -1;
    this->_checkpoints = new QMap<int, Checkpoint*>();
    this->_obstacles = new QMap<int, Obstacle*>();
}

// destructor
Field::~Field() {
    delete this->_checkpoints;
    delete this->_obstacles;
}

//  +-------+
//  | UTILS |
//  +-------+
/**
 * transform QJsonObject to UserService
 * @param json
 */
void Field::deserialize(const QJsonObject &jsonObject) {
    this->_mapWidth = jsonObject["mapWidth"].toDouble();
    this->_mapHeight = jsonObject["mapHeight"].toDouble();

    QJsonArray jsonCheckpoints = jsonObject["checkpoints"].toArray();

    foreach(const QJsonValue &value, jsonCheckpoints) {
        QJsonObject checkpointJsonObject = value.toObject();
        Checkpoint *checkpoint = this->_checkpoints->value(checkpointJsonObject["id"].toInt());

        if (checkpoint) {
            checkpoint->deserialize(checkpointJsonObject);
            this->_checkpoints->insert(checkpoint->getId(), checkpoint);
        }
    }

    QJsonArray jsonObstacles = jsonObject["obstacles"].toArray();

    foreach(const QJsonValue &value, jsonObstacles) {
        QJsonObject obstacleJsonObject = value.toObject();
        Obstacle *obstacle = this->_obstacles->value(obstacleJsonObject["id"].toInt());

        if (obstacle) {
            obstacle->deserialize(obstacleJsonObject);
            this->_obstacles->insert(obstacle->getId(), obstacle);
        }
    }
}

QString Field::serialize() {
    QJsonDocument doc(this->toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}

QJsonObject Field::toJson() {
    QJsonObject jObject;

    auto checkpointJA = QJsonArray();
    auto obstaclesJA = QJsonArray();

    for (auto & checkpoint : this->_checkpoints->values())
        checkpointJA.append(checkpoint->toJson());

    jObject["checkpoints"] = checkpointJA;

    for (auto & obstacle : this->_obstacles->values())
        obstaclesJA.append(obstacle->toJson());

    jObject["obstacles"] = obstaclesJA;

    jObject["mapWidth"] = this->_mapWidth;
    jObject["mapHeight"] = this->_mapHeight;

    return jObject;
}


bool Field::setMapInfo(cv::Mat &pImage)
{
    this->_checkpoints = new QMap<int, Checkpoint*>();
    this->_obstacles = new QMap<int, Obstacle*>();

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
        for (std::vector<std::vector< cv::Point2f >>::iterator nCorner = corners.begin() ; nCorner != corners.end(); nCorner++) {
            // reset pos
            itemPos.x = 9999;
            itemPos.y = 0;
            for (std::vector< cv::Point2f >::iterator nPoint = nCorner->begin() ; nPoint != nCorner->end(); nPoint++) {
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
                this->_checkpoints->insert(checkpoint->getId(), checkpoint);
            } else if(ids[itId] > 9 && ids[itId] < 250) {
                Obstacle *obstacle = new Obstacle();
                obstacle->setId(ids[itId]);
                obstacle->setX(itemPos.x);
                obstacle->setY(itemPos.y);
                obstacle->setAngle(0);
                this->_obstacles->insert(obstacle->getId(), obstacle);
            }

            itId++;
        }

        // enregistrement des limites map
        this->_mapWidth = topRight.x;
        this->_mapHeight = topRight.y;
    }

    //afficher la sortie
    cv::imshow("out", imageCopy);

    return success;
}

//  +--------+
//  | SETTER |
//  +--------+
void Field::setMapWidth(float pMapWidth)
{
    this->_mapWidth = pMapWidth;
}

void Field::setMapHeight(float pMapHeight)
{
    this->_mapHeight = pMapHeight;
}

void Field::addCheckpoint(Checkpoint *pCheckpoint)
{
    this->_checkpoints->insert(pCheckpoint->getId(), pCheckpoint);
}

void Field::addObstacle(Obstacle *pObstacle) {
    this->_obstacles->insert(pObstacle->getId(), pObstacle);
}

//  +--------+
//  | GETTER |
//  +--------+
float Field::getMapWidth()
{
    return this->_mapWidth;
}

float Field::getMapHeight()
{
    return this->_mapHeight;
}
