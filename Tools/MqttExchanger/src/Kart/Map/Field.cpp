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
