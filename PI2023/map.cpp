#include "map.h"


Map::Map()
{

}

void Map::setHeight(int height)
{
    m_height = height;
}
int Map::getHeight()
{
    return m_height;
}


void Map::setWigth(int wigth)
{
    m_wigth = wigth;
}
int Map::getWigth()
{
    return m_wigth;
}
void Map::deserialize(const QJsonObject &jsonObject) {
    this->m_wigth= jsonObject["mapWidth"].toDouble();
    this->m_height= jsonObject["mapHeight"].toDouble();

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

    jObject["mapWidth"] = this->m_wigth;
    jObject["mapHeight"] = this->m_height;

    return jObject;
}
