#include "Player.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Player::Player(QObject *parent)
    : QObject{parent}
{

}

void Player::deserialize(const QJsonObject &jsonObject) {
    uuid = jsonObject["uuid"].toString();
    pseudo = jsonObject["pseudo"].toString();
    color = jsonObject["color"].toString();
    team = jsonObject["team"].toString();
    speed = jsonObject["speed"].toInt();
    vehicle = jsonObject["vehicle"].toString();

    auto itemsJObject = jsonObject["items"].toObject();
    items->insert("banana", itemsJObject["banana"].toInt());
    items->insert("bomb", itemsJObject["bomb"].toInt());
    items->insert("rocket", itemsJObject["rocket"].toInt());

    lastCheckpoint = jsonObject["lastCheckpoint"].toInt();

    currentLap = jsonObject["currentLap"].toInt();
    status = jsonObject["status"].toString();
    controller = jsonObject["controller"].toString();
}

QJsonObject Player::toJson() {
    QJsonObject jsonObject;

    jsonObject["uuid"] = this->uuid;
    jsonObject["pseudo"] = this->pseudo;
    jsonObject["color"] = this->color;
    jsonObject["team"] = this->team;
    jsonObject["speed"] = this->speed;
    jsonObject["vehicle"] = this->vehicle;

    QJsonObject itemsJO;

    itemsJO.insert("banana", items->value("banana"));
    itemsJO.insert("bomb", items->value("bomb"));
    itemsJO.insert("rocket", items->value("rocket"));

    jsonObject["items"] = itemsJO;

    jsonObject["lastCheckpoint"] = this->lastCheckpoint;

    jsonObject["currentLap"] = this->currentLap;
    jsonObject["status"] = this->status;
    jsonObject["controller"] = this->controller;

    return jsonObject;
}

QString Player::serialize() {
    QJsonDocument doc(this->toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}
