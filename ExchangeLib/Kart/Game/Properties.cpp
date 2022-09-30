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

    circleRadius = jsonObject["circleRadius"].toInt();
    rectangleWidth = jsonObject["rectangleWidth"].toInt();
    rectangleHeight = jsonObject["rectangleHeight"].toInt();
    checkpointRadius = jsonObject["checkpointRadius"].toInt();

    banana = jsonObject["bananaNb"].toInt();
    bananaCooldown = jsonObject["bananaCd"].toInt();
    bananaTTL = jsonObject["bananaTtl"].toInt();
    bananaRadius = jsonObject["bananaRadius"].toInt();

    bomb = jsonObject["bombNb"].toInt();
    bombCooldown = jsonObject["bombCd"].toInt();
    bombTTL = jsonObject["bombTtl"].toInt();
    bombRadius = jsonObject["bombRadius"].toInt();
    bombExplosionRadius = jsonObject["bombExplosionRadius"].toInt();

    rocket = jsonObject["rocketNb"].toInt();
    rocketCooldown = jsonObject["rocketCd"].toInt();
    rocketSpeed = jsonObject["rocketSpeed"].toDouble();
    rocketRadius = jsonObject["rocketRadius"].toInt();
    QJsonObject vehicleOptionsJO = jsonObject["vehicleOptions"].toObject();
    for (const QString &key: vehicleOptionsJO.keys()) {
        QJsonObject userJsonObject = vehicleOptionsJO.value(key).toObject();
        Vehicle *vehicle = vehicleOptions->value(key);

        if (!vehicle) {
            vehicle = new Vehicle();
        }

        QJsonObject vehicleJO = vehicleOptionsJO[key].toObject();
        vehicle->deserialize(vehicleJO);
        vehicle->setType(key);
        this->vehicleOptions->insert(key , vehicle);

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
    jObject["bananaCd"] = this->bananaCooldown;
    jObject["bananaTtl"] = this->bananaTTL;
    jObject["bananaRadius"] = this->bananaRadius;

    jObject["bombNb"] = this->bomb;
    jObject["bombTtl"] = this->bombTTL;
    jObject["bombCd"] = this->bombCooldown;
    jObject["bombRadius"] = this->bombRadius;

    jObject["rocketNb"] = this->rocket;
    jObject["rocketCd"] = this->rocketCooldown;
    jObject["rocketSpeed"] = this->rocketSpeed;
    jObject["rocketRadius"] = this->rocketRadius;

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
