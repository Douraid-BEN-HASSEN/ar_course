#include "Player.h"

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
    controller = jsonObject["controller"].toString();;
}
