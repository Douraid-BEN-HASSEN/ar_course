#include "Vehicle.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Vehicle::Vehicle(int maxSpeed, float acceleration, int weight, float steeringAngle , QString type, QObject *parent): QObject{parent}
{
    this->maxSpeed = maxSpeed;
    this->acceleration = acceleration ;
    this->weight = weight ;
    this->steeringAngle = steeringAngle ;
    this->type = type;
}

Vehicle::Vehicle(QString type, QObject *parent): QObject{parent}
{
    this->type = type;

    if(this->type == "bike") {
        this->maxSpeed = 100;
        this->acceleration = 10;
        this->weight = 200;
        this->height = 15;
        this->width = 5;
        this->steeringAngle = 1,0472; //60°
    } else if(this->type == "car") {
        this->maxSpeed = 75;
        this->acceleration = 10;
        this->weight = 1500;
        this->height = 20;
        this->width = 10;
        this->steeringAngle = 0,785398; // 45°
    } else if(this->type == "truck") {
        this->maxSpeed = 60;
        this->acceleration = 10;
        this->weight = 3500;
        this->height = 25;
        this->width = 12;
        this->steeringAngle = 0,523599; //30°
    }
}

QString Vehicle::toString() {
    return QString("MaxSpeed %1 | Acceleration : %2 | Weight : %3 | Height : %4, Width %5 | Angle : %6").arg(
                QString::number(this->maxSpeed),
                QString::number(this->acceleration),
                QString::number(this->weight),
                QString::number(this->height),
                QString::number(this->width),
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
    this->width = jsonObject["width"].toInt();
    this->height = jsonObject["height"].toInt();
}

QJsonObject Vehicle::toJson() {
    QJsonObject jObject;
    jObject["maxSpeed"] = this->maxSpeed;
    jObject["acceleration"] = this->acceleration;
    jObject["weight"] = this->weight;
    jObject["steeringAngle"] = this->steeringAngle;
    jObject["width"] = this->width;
    jObject["height"] = this->height;

    return jObject;
}

float Vehicle::getMaxSpeed()
{
    return this->maxSpeed;
}

float Vehicle::getAcceleration()
{
    return this->acceleration;
}

float Vehicle::getWeight()
{
    return this->weight;
}

float Vehicle::getSteeringAngle()
{
    return this->steeringAngle;
}

int Vehicle::getWidth()
{
    return this->width;
}

int Vehicle::getHeight()
{
    return this->height;
}


void Vehicle::setType(QString type) {
    this->type = type ;
}

QString Vehicle::getType() {
    return this->type ;
}
QString Vehicle::serialize() {
    QJsonDocument doc(this->toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}
