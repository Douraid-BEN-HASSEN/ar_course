#include "Properties.h"

Properties *Properties::getInstance() {
    if (_instance == nullptr) {
        _instance = new Properties;
        MqttService::instance()->subscribe(_instance->topic);
        connect(MqttService::instance(), &MqttService::message, _instance, &Properties::receivedMessage);
    }

    return _instance;
}

Properties::Properties(QObject *parent) : QObject{parent} {}

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
        qDebug() << "new vehicle";
        QJsonObject userJsonObject = vehicleOptionsJO.value(key).toObject();

        Vehicle *vehicle = vehicleOptions->value(key);

        if (!vehicle) {
            vehicle = new Vehicle();
        }

        QJsonObject vehicleJO = vehicleOptionsJO[key].toObject();
        vehicle->deserialize(vehicleJO);
    }

    emit updated();
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


/**
 * |-------------------|
 * | getter and setter |
 * |-------------------|
 */
int Properties::getLaps() const {
    return laps;
}

void Properties::setLaps(int laps) {
    this->laps = laps;
}

int Properties::getTeam() const {
    return team;
}

void Properties::setTeam(int team) {
    this->team = team;
}

int Properties::getBanana() const {
    return banana;
}

void Properties::setBanana(int banana) {
    this->banana = banana;
}

int Properties::getBananaCooldown() const {
    return bananaCooldown;
}

void Properties::setBananaCooldown(int bananaCooldown) {
    this->bananaCooldown = bananaCooldown;
}

int Properties::getBananaTtl() const {
    return bananaTTL;
}

void Properties::setBananaTtl(int bananaTtl) {
    bananaTTL = bananaTtl;
}

int Properties::getBananaRadius() const {
    return bananaRadius;
}

void Properties::setBananaRadius(int bananaRadius) {
    this->bananaRadius = bananaRadius;
}

int Properties::getBomb() const {
    return bomb;
}

void Properties::setBomb(int bomb) {
    this->bomb = bomb;
}

int Properties::getBombCooldown() const {
    return bombCooldown;
}

void Properties::setBombCooldown(int bombCooldown) {
    this->bombCooldown = bombCooldown;
}

int Properties::getBombTtl() const {
    return bombTTL;
}

void Properties::setBombTtl(int bombTtl) {
    bombTTL = bombTtl;
}

int Properties::getBombRadius() const {
    return bombRadius;
}

void Properties::setBombRadius(int bombRadius) {
    this->bombRadius = bombRadius;
}

int Properties::getBombExplosionRadius() const {
    return bombExplosionRadius;
}

void Properties::setBombExplosionRadius(int bombExplosionRadius) {
    this->bombExplosionRadius = bombExplosionRadius;
}

int Properties::getRocket() const {
    return rocket;
}

void Properties::setRocket(int rocket) {
    this->rocket = rocket;
}

int Properties::getRocketCooldown() const {
    return rocketCooldown;
}

void Properties::setRocketCooldown(int rocketCooldown) {
    this->rocketCooldown = rocketCooldown;
}

float Properties::getRocketSpeed() const {
    return rocketSpeed;
}

void Properties::setRocketSpeed(float rocketSpeed) {
    this->rocketSpeed = rocketSpeed;
}

int Properties::getRocketRadius() const {
    return rocketRadius;
}

void Properties::setRocketRadius(int rocketRadius) {
    this->rocketRadius = rocketRadius;
}

int Properties::getCircleRadius() const {
    return circleRadius;
}

void Properties::setCircleRadius(int circleRadius) {
    this->circleRadius = circleRadius;
}

int Properties::getRectangleWidth() const {
    return rectangleWidth;
}

void Properties::setRectangleWidth(int rectangleWidth) {
    this->rectangleWidth = rectangleWidth;
}

int Properties::getRectangleHeight() const {
    return rectangleHeight;
}

void Properties::setRectangleHeight(int rectangleHeight) {
    this->rectangleHeight = rectangleHeight;
}

int Properties::getCheckpointRadius() const {
    return checkpointRadius;
}

void Properties::setCheckpointRadius(int checkpointRadius) {
    this->checkpointRadius = checkpointRadius;
}
