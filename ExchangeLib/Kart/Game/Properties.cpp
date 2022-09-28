#include "Properties.h"

Properties::Properties(QObject *parent) : QObject{parent}
{
    MqttService::instance()->subscribe(Properties::topic);
}

void Properties::receivedMessage(QJsonObject message, QString topic) {
    if (topic == Properties::topic) {
        this->deserialize(message);
    }
}

void Properties::deserialize(const QJsonObject &jsonObject) {

    laps = jsonObject["lapsNb"].toInt();
    team = jsonObject["teamNb"].toInt();

    circleRadius = jsonObject["circleRadius"].toDouble();
    rectangleWidth = jsonObject["rectangleWidth"].toDouble();
    rectangleHeight = jsonObject["rectangleHeight"].toDouble();
    checkpointRadius = jsonObject["checkpointRadius"].toDouble();

    banana = jsonObject["bananaNb"].toInt();
    bomb = jsonObject["bombNb"].toInt();
    rocket = jsonObject["rocketNb"].toInt();

    bananaCooldown = jsonObject["bananaCd"].toInt();
    bombCooldown = jsonObject["bombCd"].toInt();
    rocketCooldown = jsonObject["rocketCd"].toInt();

    rocketSpeed = jsonObject["rocketSpeed"].toDouble();
    bananaTTL = jsonObject["bananaTtl"].toDouble();
    bombTTL = jsonObject["bombTtl"].toDouble();

    QJsonObject vehicleOptionsJO = jsonObject["vehicleOptions"].toObject();

    for (const QString &key: vehicleOptionsJO.keys()) {
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

    jObject["lapsNb"] = this->laps;
    jObject["teamNb"] = this->team;

    jObject["circleRadius"] = this->circleRadius;
    jObject["rectangleWidth"] = this->rectangleWidth;
    jObject["rectangleHeight"] = this->rectangleHeight;
    jObject["checkpointRadius"] = this->checkpointRadius;

    jObject["bananaNb"] = this->banana;
    jObject["bombNb"] = this->bomb;
    jObject["rocketNb"] = this->rocket;

    jObject["bananaCd"] = this->bananaCooldown;
    jObject["bombCd"] = this->bombCooldown;
    jObject["rocketCd"] = this->rocketCooldown;

    jObject["rocketSpeed"] = this->rocketSpeed;
    jObject["bananaTtl"] = this->bananaTTL;
    jObject["bombTtl"] = this->bombTTL;

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
