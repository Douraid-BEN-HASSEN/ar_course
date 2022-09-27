#include "Field.h"

Field *Field::instance() {
    static Field instance;
    return &instance;
}

Field::Field(QObject *parent): QObject{parent}
{
}

/**
 * transform QJsonObject to UserService
 * @param json
 */
void Field::deserialize(const QJsonObject &jsonObject) {
    width = jsonObject["width"].toDouble();
    height = jsonObject["height"].toDouble();

    QJsonArray jsonCheckpoints = jsonObject["checkpoints"].toArray();

    foreach(const QJsonValue &value, jsonCheckpoints) {
        QJsonObject checkpointJsonObject = value.toObject();
        Checkpoint *checkpoint = checkpoints->value(checkpointJsonObject["id"].toInt());

        if (!checkpoint) {
            checkpoint = new Checkpoint();
        }

        checkpoint->deserialize(checkpointJsonObject);
        checkpoints->insert(checkpoint->id, checkpoint);
    }

    QJsonArray jsonObstacles = jsonObject["obstacles"].toArray();

    foreach(const QJsonValue &value, jsonObstacles) {
        QJsonObject obstacleJsonObject = value.toObject();
        Obstacle *obstacle = obstacles->value(obstacleJsonObject["id"].toInt());

        if (!obstacle) {
            obstacle = new Obstacle();
        }

        obstacle->deserialize(obstacleJsonObject);
        obstacles->insert(obstacle->id, obstacle);
    }
}

QJsonObject Field::toJson() {
    QJsonObject jObject;
    jObject["width"] = this->width;
    jObject["height"] = this->height;

    auto obstaclesJA = QJsonArray();

    for (auto & obstacle : obstacles->values())
        obstaclesJA.append(obstacle->toJson());

    jObject["obstacles"] = obstaclesJA;

    return jObject;
}


QString Field::serialize() {
    QJsonDocument doc(this->toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}
