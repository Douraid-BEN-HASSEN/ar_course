#include "Map.h"

Map *Map::instance() {
    static Map instance;
    return &instance;
}

// constructor
Map::Map(QObject *parent): QObject{parent}
{
    MqttService::instance()->subscribe(Map::topic);

    this->_mapWidth = -1;
    this->_mapHeight = -1;
    this->_checkpoints = new QMap<int, Checkpoint*>();
    this->_obstacles = new QMap<int, Obstacle*>();

    /* -- connect -- */
    /* todo implmente an interface and methode to connect */
    connect(MqttService::instance(), &MqttService::message, this, &Map::receivedMessage);
}

// destructor
Map::~Map() {
    delete this->_checkpoints;
    delete this->_obstacles;
}

void Map::receivedMessage(QJsonObject message, QString topic) {
    if (topic == Map::topic) {
        this->deserialize(message);
    }

}

//  +-------+
//  | UTILS |
//  +-------+
/**
 * transform QJsonObject to UserService
 * @param json
 */
void Map::deserialize(const QJsonObject &jsonObject) {
    this->_mapWidth = jsonObject["mapWidth"].toDouble();
    this->_mapHeight = jsonObject["mapHeight"].toDouble();

    QJsonArray jsonCheckpoints = jsonObject["checkpoints"].toArray();

    foreach(const QJsonValue &value, jsonCheckpoints) {
        QJsonObject checkpointJsonObject = value.toObject();
        Checkpoint *checkpoint = this->_checkpoints->value(checkpointJsonObject["id"].toInt());

        if (!checkpoint) {
            checkpoint = new Checkpoint();
        }

        checkpoint->deserialize(checkpointJsonObject);
        this->_checkpoints->insert(checkpoint->getId(), checkpoint);
    }

    QJsonArray jsonObstacles = jsonObject["obstacles"].toArray();

    foreach(const QJsonValue &value, jsonObstacles) {
        QJsonObject obstacleJsonObject = value.toObject();
        Obstacle *obstacle = this->_obstacles->value(obstacleJsonObject["id"].toInt());

        if (!obstacle) {
            obstacle = new Obstacle();
        }

        obstacle->deserialize(obstacleJsonObject);
        _obstacles->insert(obstacle->getId(), obstacle);
    }

    emit mapUpadeted();
}

QString Map::serialize() {
    QJsonDocument doc(this->toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}

QJsonObject Map::toJson() {
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

/**
 *  +--------+
 *  | SETTER |
 *  +--------+
 */

void Map::setMapWidth(float pMapWidth)
{
    this->_mapWidth = pMapWidth;
}

void Map::setMapHeight(float pMapHeight)
{
    this->_mapHeight = pMapHeight;
}

void Map::addCheckpoint(Checkpoint *pCheckpoint)
{
    this->_checkpoints->insert(pCheckpoint->getId(), pCheckpoint);
}

void Map::addObstacle(Obstacle *pObstacle) {
    this->_obstacles->insert(pObstacle->getId(), pObstacle);
}

/**
 *  +--------+
 *  | GETTER |
 *  +--------+
 */

float Map::getMapWidth()
{
    return this->_mapWidth;
}

float Map::getMapHeight()
{
    return this->_mapHeight;
}

QMap<int, Checkpoint *>* Map::getCheckpoints()
{
    return this->_checkpoints;
}

QMap<int, Obstacle*>* Map::getObstacles()
{
    return this->_obstacles;
}


