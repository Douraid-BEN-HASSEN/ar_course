#include "Item.h"

Item::Item(QObject *parent): QObject{parent}
{

}

void Item::deserialize(const QJsonObject &jsonObject) {
    this->_x = jsonObject["x"].toInt();
    this->_y = jsonObject["x"].toInt();
    this->_angle = jsonObject["angle"].toDouble();
    this->_status = jsonObject["status"].toString();
    this->_type = jsonObject["type"].toString();
}

void Item::setX(int pX)
{
 this->_x=pX;
}

void Item::setY(int pY)
{
    this->_y=pY;
}

void Item::setAngle(float pAngle)
{
    this->_angle=pAngle;
}

void Item::setStatus(QString pStatut)
{
    this->_status=pStatut;
}

int Item::getX()
{
return this->_x;
}

int Item::getY()
{
return this->_y;
}

float Item::getAngle()
{
    return this->_angle;
}

QString Item::getStatus()
{
    return this->_status;
}

QString Item::getType()
{
    return this->_type;
}
