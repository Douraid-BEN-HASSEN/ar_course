#include "Field.h"

Field *Field::instance() {
    static Field instance;
    return &instance;
}

//connect(button_downServer, SIGNAL(clicked()), qApp, SLOT(quit()));



Field::Field(QObject *parent): QObject{parent}
{

}

/**
 * transform QJsonObject to UserService
 * @param json
 */
void Field::deserialize(const QJsonObject &jsonObject) {
    width = jsonObject["mapWidth"].toDouble();
    height = jsonObject["mapHeight"].toDouble();

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
    emit fieldUpadeted();
}
