#include "Item.h"
#include "qpoint.h"

Item::Item(QObject *parent): QObject{parent}
{

}

Item::Item(QPoint point, float angle, QString type, QObject *parent): QObject{parent}
{
    this->_uuid = QUuid::createUuid().toString();
    this->_x = point.x();
    this->_y = point.y();
    this->_type = type;
}

Item::Item(int x, int y, float angle, QString type, QObject *parent): QObject{parent}
{
    this->_uuid = QUuid::createUuid().toString();
    this->_angle = angle;
    this->_x = x;
    this->_y = y;
    this->_type = type;
}

//  +-------+
//  | UTILS |
//  +-------+
void Item::deserialize(const QJsonObject &jsonObject) {
    this->_uuid = jsonObject["uuid"].toString();
    this->_x = jsonObject["x"].toInt();
    this->_y = jsonObject["y"].toInt();
    this->_angle = jsonObject["angle"].toDouble();
    this->_status = jsonObject["status"].toString();
    this->_type = jsonObject["type"].toString();
}

QString Item::serialize() {
    QJsonDocument doc(this->toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}

QJsonObject Item::toJson() {
    QJsonObject jsonObject;

    jsonObject["uuid"] = this->_uuid;
    jsonObject["x"] = this->_x;
    jsonObject["y"] = this->_y;
    jsonObject["status"] = this->_status;
    jsonObject["type"] = this->_type;

    return jsonObject;
}

//  +--------+
//  | SETTER |
//  +--------+

void Item::setPos(const QPoint &pos)
{
    this->_x = pos.x();
    this->_y = pos.y();
}

inline void Item::setPos(int x, int y)
{
    setPos(QPoint(x, y));
}

void Item::setX(int pX)
{
    this->_x = pX;
}

void Item::setY(int pY)
{
    this->_y = pY;
}

void Item::setAngle(float pAngle)
{
    this->_angle = pAngle;
}

void Item::setStatus(QString pStatut)
{
    this->_status = pStatut;
}

//  +--------+
//  | GETTER |
//  +--------+
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
QString Item::getUuid()
{
    return this->_uuid;
}
