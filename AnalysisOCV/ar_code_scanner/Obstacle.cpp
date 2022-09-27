#include "obstacle.h"

Obstacle::Obstacle(QObject *parent)
    : QObject{parent}
{

}

void Obstacle::deserialize(const QJsonObject &jsonObject) {
    id = jsonObject["id"].toInt();
    x = jsonObject["x"].toInt();
    y = jsonObject["y"].toInt();
    angle = jsonObject["angle"].toDouble();
}
