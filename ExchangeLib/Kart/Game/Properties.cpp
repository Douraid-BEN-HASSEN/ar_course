#include "Properties.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Properties::Properties(QObject *parent) : QObject{parent} {

}

void Properties::deserialize(const QJsonObject &jsonObject) {

    laps = jsonObject["laps"].toInt();
    team = jsonObject["team"].toInt();

    circleRadius = jsonObject["circleRadius"].toDouble();
    rectangleWidth = jsonObject["rectangleWidth"].toDouble();
    rectangleHeight = jsonObject["rectangleHeight"].toDouble();
    checkpointRadius = jsonObject["checkpointRadius"].toDouble();

    banana = jsonObject["banana"].toInt();
    bomb = jsonObject["bomb"].toInt();
    rocket = jsonObject["rocket"].toInt();

    bananaCooldown = jsonObject["bananaCooldown"].toInt();
    bombCooldown = jsonObject["bombCooldown"].toInt();
    rocketCooldown = jsonObject["rocketCooldown"].toInt();

    rocketSpeed = jsonObject["rocketSpeed"].toDouble();
    bananaTTL = jsonObject["bananaTTL"].toDouble();
    bombTTL = jsonObject["bombTTL"].toDouble();

    QJsonObject vehicleOptionsJO = jsonObject["vehicleOptions"].toObject();

            foreach(const QString &key, vehicleOptionsJO.keys()) {
            QJsonObject userJsonObject = vehicleOptionsJO.value(key).toObject();

            Vehicle *vehicle = vehicleOptions->value(key);

            if (!vehicle) {
                vehicle = new Vehicle();
            }

            QJsonObject vehicleJO = vehicleOptionsJO[key].toObject();
            vehicle->deserialize(vehicleJO);

        }
}

QJsonObject Properties::toJson() {
    QJsonObject jObject;

    jObject["laps"] = this->laps;
    jObject["team"] = this->team;

    jObject["circleRadius"] = this->circleRadius;
    jObject["rectangleWidth"] = this->rectangleWidth;
    jObject["rectangleHeight"] = this->rectangleHeight;
    jObject["checkpointRadius"] = this->checkpointRadius;

    jObject["banana"] = this->banana;
    jObject["bomb"] = this->bomb;
    jObject["rocket"] = this->rocket;

    jObject["bananaCooldown"] = this->bananaCooldown;
    jObject["bombCooldown"] = this->bombCooldown;
    jObject["rocketCooldown"] = this->rocketCooldown;

    jObject["rocketSpeed"] = this->rocketSpeed;
    jObject["bananaTTL"] = this->bananaTTL;
    jObject["bombTTL"] = this->bombTTL;

    QJsonObject vehicleOptionsJO = QJsonObject();

    QMapIterator<QString, Vehicle *> i(*vehicleOptions);
    while (i.hasNext()) {
        i.next();
        vehicleOptionsJO.insert(i.key(), i.value()->toJson());
    }

    jObject["vehicleOptions"] = vehicleOptionsJO;

    return jObject;
}

QString Properties::serialize() {
    QJsonDocument doc(this->toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}
