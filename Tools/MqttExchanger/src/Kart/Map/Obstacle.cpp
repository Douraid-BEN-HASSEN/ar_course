#include "Obstacle.h"

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

QJsonObject Obstacle::toJson() {
    QJsonObject jObject;

    /* set key -> value of json */
    jObject["id"] = this->id;
    jObject["x"] = this->x;
    jObject["y"] = this->y;
    jObject["angle"] = this->angle;

    return jObject;

}
