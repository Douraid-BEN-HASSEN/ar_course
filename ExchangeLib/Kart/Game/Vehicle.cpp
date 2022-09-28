#include "Vehicle.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Vehicle::Vehicle(QObject *parent): QObject{parent}
{
}

Vehicle::Vehicle(int maxSpeed, float acceleration, int weight, float steeringAngle , QString type, QObject *parent): QObject{parent}
{
    this->maxSpeed = maxSpeed;
    this->acceleration = acceleration ;
    this->weight = weight ;
    this->steeringAngle = steeringAngle ;
    this->type = type ;
}


QString Vehicle::toString() {
    return QString("Type : %1 | MS : %2 | A : %3 | W : %4 | SA : %5").arg(
                this->type,
                QString::number(this->maxSpeed),
                QString::number(this->acceleration),
                QString::number(this->weight),
                QString::number(this->steeringAngle)
                );

}

/**
 * transform QJsonObject to UserService
 * @param json
 */
void Vehicle::deserialize(const QJsonObject &jsonObject) {
    this->maxSpeed = jsonObject["maxSpeed"].toInt();
    this->acceleration = jsonObject["acceleration"].toDouble();
    this->weight = jsonObject["weight"].toInt();
    this->steeringAngle = jsonObject["steeringAngle"].toDouble();
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
