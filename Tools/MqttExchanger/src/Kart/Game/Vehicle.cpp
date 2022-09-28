#include "Vehicle.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Vehicle::Vehicle(QObject *parent)
    : QObject{parent}
{


}


/**
 * transform QJsonObject to UserService
 * @param json
 */
void Vehicle::deserialize(const QJsonObject &jsonObject) {
    maxSpeed = jsonObject["maxSpeed"].toInt();
    acceleration = jsonObject["acceleration"].toDouble();
    weight = jsonObject["weight"].toInt();
    steeringAngle = jsonObject["steeringAngle"].toDouble();
}

QJsonObject Vehicle::toJson() {
    QJsonObject jObject;
    jObject["maxSpeed"] = this->maxSpeed;
    jObject["acceleration"] = this->acceleration;
    jObject["weight"] = this->weight;
    jObject["steeringAngle"] = this->weight;

    return jObject;
}


QString Vehicle::serialize() {
    QJsonDocument doc(this->toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}
