#include "Register.h"

Register::Register(QObject *parent): QObject{parent}
{
    _uuid = QUuid::createUuid().toString();

}

Register::Register(QString pseudo, QString controller, QString vehicle, int team, QObject *parent): QObject{parent}
{
    _uuid = QUuid::createUuid().toString();
    _pseudo = pseudo;
    _controller = controller;
    _vehicle = vehicle;
    _team = team;

}

void Register::publish() {
    MqttService::instance()->publish(this->topic, this->serialize());
}

//  +-------+
//  | UTILS |
//  +-------+
QString Register::toString() {
    return QString("uuid: %1, pseudo: %2, controller: %3, vehicle: %4, team: %5 ").arg(_uuid, _pseudo, _controller, _vehicle, QString::number(_team));
}

void Register::deserialize(const QJsonObject &jsonObject)
{
    this->_uuid = jsonObject["uuid"].toString();
    this->_pseudo = jsonObject["pseudo"].toString();
    this->_controller = jsonObject["controller"].toString();
    this->_vehicle = jsonObject["vehicle"].toString();
    this->_team = jsonObject["team"].toInt();
}

QString Register::serialize() {
    QJsonDocument doc(this->toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}

QJsonObject Register::toJson() {
    QJsonObject jsonObject;

    jsonObject["uuid"] = this->_uuid;
    jsonObject["pseudo"] = this->_pseudo;
    jsonObject["controller"] = this->_controller;
    jsonObject["vehicle"] = this->_vehicle;
    jsonObject["team"] = this->_team;

    return jsonObject;
}

QString Register::getUuid()
{
    return _uuid;
}

QString Register::getPseudo()
{
    return _pseudo;
}

QString Register::getController()
{
    return _controller;
}

QString Register::getVehicle()
{
    return _vehicle;
}

int Register::getTeam() {
    return _team;
}
