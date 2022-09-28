#include "Checkpoint.h"

// constructor
Checkpoint::Checkpoint(QObject *parent): QObject{ parent }
{
}

// destructor
Checkpoint::~Checkpoint() {}

//  +-------+
//  | UTILS |
//  +-------+
void Checkpoint::deserialize(const QJsonObject &jsonObject) {
    this->_id = jsonObject["id"].toInt();
    this->_x = jsonObject["x"].toInt();
    this->_y = jsonObject["y"].toInt();
    this->_timeout = jsonObject["timeout"].toInt();
}

QString Checkpoint::serialize()
{
    QJsonDocument doc(this->toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}

QJsonObject Checkpoint::toJson()
{
    QJsonObject jObject;
    jObject["id"] = this->_id;
    jObject["x"] = this->_x;
    jObject["y"] = this->_y;
    jObject["timeout"] = this->_timeout;

    return jObject;
}

//  +--------+
//  | SETTER |
//  +--------+
void Checkpoint::setId(int pId) {
    this->_id = pId;
}

void Checkpoint::setX(int pX) {
    this->_x = pX;
}

void Checkpoint::setY(int pY) {
    this->_y = pY;
}

void Checkpoint::setTimeout(int pTimeout)
{
    this->_timeout = pTimeout;
}

//  +--------+
//  | GETTER |
//  +--------+
int Checkpoint::getId() {
    return this->_id;
}

int Checkpoint::getX() {
    return this->_x;
}

int Checkpoint::getY() {
    return this->_y;
}

int Checkpoint::getTimeout()
{
    return this->_timeout;
}

