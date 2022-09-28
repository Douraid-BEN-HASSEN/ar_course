#include "properties.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Properties::Properties(QObject *parent)
    : QObject{parent}
{

}

void Properties::deserialize(const QJsonObject &jsonObject) {
    lapsNb = jsonObject["lapsNb"].toInt();
    teamNb = jsonObject["teamNb"].toInt();
    circleRadius = jsonObject["circleRadius"].toDouble();
    rectangleWidth = jsonObject["rectangleWidth"].toDouble();
    rectangleHeight = jsonObject["rectangleHeight"].toDouble();
    checkpointRadius = jsonObject["checkpointRadius"].toDouble();
    bananaNb = jsonObject["bananaNb"].toInt();
    bombNb = jsonObject["bombNb"].toInt();
    rocketNb = jsonObject["rocketNb"].toInt();
    bananaCd = jsonObject["bananaCd"].toInt();
    bombCd = jsonObject["bombCd"].toInt();
    rocketCd = jsonObject["rocketCd"].toInt();
    rocketSpeed = jsonObject["rocketSpeed"].toDouble();
    bananaTtL = jsonObject["bananaTtL"].toDouble();
    bombTtL = jsonObject["bombTtL"].toDouble();

    QJsonArray vehiclesArray=  jsonObject["vehicleOptions"].toArray() ;
    for (int i = 0 ; i < vehiclesArray.size() ; i++) {
        qDebug () << vehiclesArray.at(i) ;
        qDebug() << vehiclesArray.at(i).toObject().value("acceleration").toDouble();
        this->vehicleOptions->append(new Vehicle(vehiclesArray.at(i).toObject().value("maxSpeed").toInt() , vehiclesArray.at(i).toObject().value("acceleration").toDouble() , vehiclesArray.at(i).toObject().value("weight").toInt() , vehiclesArray.at(i).toObject().value("steeringAngle").toDouble() , vehiclesArray.at(i).toObject().value("vehicle").toString()));
    }
}

QJsonObject Properties::toJson() {
    QJsonObject jObject;
    jObject["lapsNb"] = this->lapsNb;
    jObject["teamNb"] = this->teamNb;
    jObject["circleRadius"] = this->circleRadius;
    jObject["rectangleWidth"] = this->rectangleWidth;
    jObject["rectangleHeight"] = this->rectangleHeight;
    jObject["checkpointRadius"] = this->checkpointRadius;
    jObject["bananaNb"] = this->bananaNb;
    jObject["bombNb"] = this->bombNb;
    jObject["rocketNb"] = this->rocketNb;
    jObject["bananaCd"] = this->bananaCd;
    jObject["bombCd"] = this->bombCd;
    jObject["rocketCd"] = this->rocketCd;
    jObject["rocketSpeed"] = this->rocketSpeed;
    jObject["bananaTtL"] = this->bananaTtL;
    jObject["bombTtL"] = this->bombTtL;
    QJsonObject vehicleOptionsJO = QJsonObject();

    /*
    QMapIterator<QString, Vehicle *> i(*vehicleOptions);
    while (i.hasNext()) {
        i.next();
        vehicleOptionsJO.insert(i.key(), i.value()->toJson());
    }
    jObject["vehicleOptions"] = vehicleOptionsJO;
    */
    return jObject;

}
QString Properties::serialize() {
    QJsonDocument doc(this->toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}
