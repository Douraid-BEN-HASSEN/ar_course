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

void Controller::handleKeyEvent(QString uuid , QKeyEvent *key ,  int *power, float *angle, int *nbBananas, int *nbBomb, int *nbRocket)
{
    int keyAction = key->key() == Qt::Key_1 ? 1 : key->key() == Qt::Key_2 ? 2 : key->key() == Qt::Key_3 ? 3 : 0  ;

    bool isCorrectAction = ( keyAction == 1 && *nbBananas > 0) || (keyAction == 2 && *nbBomb > 0) || (keyAction ==3 && *nbRocket > 0) ? true : false  ;
    qDebug() << "test 1 ";
    switch(key->key()) {
    case Qt::Key_Z:
        this->catchKeyUp(power);
        break;
    case Qt::Key_Q:
        this->catchKeyLeft(angle);
        break ;
    case Qt::Key_S:
        this->catchKeyDown(power);
        break ;
    case Qt::Key_D:
        this->catchKeyRight(angle);
        break ;
    case Qt::Key_1:
        keyAction = 1 ;
        this->catchKeyAction(1 , nbBananas , nbBomb , nbRocket);
        break ;
    case Qt::Key_2:
        keyAction = 2 ;
        this->catchKeyAction(2 , nbBananas , nbBomb , nbRocket);
        break ;
    case Qt::Key_3:
        keyAction = 3 ;
        this->catchKeyAction(3 , nbBananas , nbBomb , nbRocket);
        break ;
    case Qt::Key_4:
        keyAction = 4 ;
        this->catchKeyAction(4 , nbBananas , nbBomb , nbRocket);
        break ;
    }


    if (isCorrectAction == true )
        this->sendMessageControl(uuid , *angle , *power , keyAction);
}

void Controller::catchKeyUp(int *power)
{
    if (*power != 100)
        *power += 1;
}

void Controller::catchKeyDown(int *power)
{
    if(*power != -100)
        *power -= 1;

}

void Controller::catchKeyRight(float *angle)
{
    if (*angle == 0)
        *angle = 270 ;
    else
        *angle -= 90;
}

void Controller::catchKeyLeft(float *angle)
{
    if (*angle == 270)
        *angle = 0 ;
    else
        *angle += 90;
}

void Controller::catchKeyAction( int idKey, int *nbBanana, int *nbBomb, int *nbRocket)
{
    if ((idKey == 1 && *nbBanana > 0) || (idKey == 2 && *nbBomb > 0) || (idKey == 3 && *nbRocket > 0))
        idKey == 1 ? *nbBanana-=1 : idKey == 2 ? *nbBomb -=1 : *nbRocket -=1 ;

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



