#include "Controller.h"
#include <QtMath>

Controller::Controller(QObject *parent): QObject{parent}
{
    this->_properties = new Properties();
    //Connect

}

Properties* Controller::getProperties()
{
    return this->_properties;
}

void Controller::sendMessageRegister(QString uuid, QString pseudo, QString controller, QString vehicle, QString team)
{
    QJsonObject messageJsonObject ;
    messageJsonObject.insert("uuid" , uuid);
    messageJsonObject.insert("pseudo" , pseudo);
    messageJsonObject.insert("controller" , controller);
    messageJsonObject.insert("vehicle" , vehicle);
    messageJsonObject.insert("team" , team == "No team" ? "null" : team);
    QJsonDocument doc(messageJsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    MqttService::instance()->publish("/player/register" , strJson);
}

void Controller::sendMessageControl(QString uuid, int angle, int power, int keyAction)
{
    qDebug() << angle ;
    QJsonObject messageJsonObject ;
    messageJsonObject.insert("uuid" , uuid);
    //Multipliez votre nombre de degrés par π/180.
    messageJsonObject.insert("angle" , qDegreesToRadians(double(angle)) );
    messageJsonObject.insert("power" , power);
    QJsonObject messageJsonButtonsObject ;
    messageJsonButtonsObject.insert("banana" , keyAction == 1 ? true : false);
    messageJsonButtonsObject.insert("bomb" , keyAction == 2 ? true : false);
    messageJsonButtonsObject.insert("rocket" , keyAction == 3 ? true : false);
    messageJsonObject.insert("buttons" , messageJsonButtonsObject);
    QJsonDocument doc(messageJsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    MqttService::instance()->publish("/player/control" , strJson);
}

