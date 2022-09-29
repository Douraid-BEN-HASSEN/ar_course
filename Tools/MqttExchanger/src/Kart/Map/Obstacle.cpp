#include "Obstacle.h"

// constructor
Obstacle::Obstacle(QObject *parent): QObject{parent}
{
    this->_timeout = 0;
}

// destructor
Obstacle::~Obstacle()
{

}

//  +-------+
//  | UTILS |
//  +-------+
void Obstacle::deserialize(const QJsonObject &jsonObject) {
    this->_id = jsonObject["id"].toInt();
    this->_x = jsonObject["x"].toInt();
    this->_y = jsonObject["y"].toInt();
    this->_angle = jsonObject["angle"].toDouble();
    this->_timeout = jsonObject["timeout"].toInt();
}

QString Obstacle::serialize()
{
    QJsonDocument doc(this->toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}

QJsonObject Obstacle::toJson()
{
    QJsonObject jObject;
    jObject["id"] = this->_id;
    jObject["x"] = this->_x;
    jObject["y"] = this->_y;
    jObject["angle"] = this->_angle;
    jObject["timeout"] = this->_timeout;

    return jObject;
}

//  +--------+
//  | SETTER |
//  +--------+
void Obstacle::setId(int pId)
{
    this->_id = pId;
}

void Obstacle::setX(int pX)
{
    this->_x = pX;
}

void Obstacle::setY(int pY)
{
    this->_y = pY;
}

void Obstacle::setAngle(float pAngle)
{
    this->_angle = pAngle;
}

void Obstacle::setTimeout(int pTimeout)
{
    this->_timeout = pTimeout;
}


//  +--------+
//  | GETTER |
//  +--------+
int Obstacle::getId()
{
    return this->_id;
}

int Obstacle::getX()
{
    return this->_x;
}

int Obstacle::getY()
{
    return this->_y;
}

float Obstacle::getAngle()
{
    return this->_angle;
}

int Obstacle::getTimeout()
{
    return this->_timeout;
}
