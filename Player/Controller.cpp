#include "Controller.h"
#include <QtMath>

Controller::Controller(QObject *parent): QObject{parent}
{
    //this->_properties = new Properties();
    this->_properties = Properties::getInstance();
    //Connect gamepad
    this->createGamepad();
}

Controller::Controller(QString *uuid, int *power, float *angle, int *nbBananas, int *nbBomb, int *nbRocket)
{
    this->uuid = uuid ;
    this->power = power ;
    this->angle = angle ;
    this->nbBananas = nbBananas ;
    this->nbBomb = nbBomb ;
    this->nbRocket = nbRocket ;
    qDebug() << "dans constructeur controller " << *this->uuid ;
    //this->_properties = new Properties();
    this->_properties = Properties::getInstance();
    //Connect gamepad
    this->createGamepad();
}

void Controller::createGamepad(){
    QLoggingCategory::setFilterRules(QStringLiteral("qt.gamepad.debug=true"));
    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    this->gamepad = new QGamepad(*gamepads.begin(), this);
    //Connect
    qDebug() << "connect gamepad" ;
    connect(gamepad, SIGNAL(buttonL1Changed(bool)), this, SLOT(handlePressTurnLeft(bool)));
    connect(gamepad, SIGNAL(buttonR1Changed(bool)), this, SLOT(handlePressTurnRight(bool)));
    connect(gamepad,SIGNAL(buttonL2Changed(double)), this, SLOT(handlePressBrak(double)));
    connect(gamepad,SIGNAL(buttonR2Changed(double)), this, SLOT(handlePressAccelerate(double)));
    connect(gamepad,SIGNAL(buttonAChanged(bool)), this, SLOT(handlePressAction1(bool)));
    connect(gamepad,SIGNAL(buttonBChanged(bool)), this, SLOT(handlePressAction2(bool)));
    connect(gamepad,SIGNAL(buttonXChanged(bool)), this, SLOT(handlePressAction3(bool)));
    connect(gamepad,SIGNAL(buttonYChanged(bool)), this, SLOT(handlePressAction4(bool)));
}

Properties* Controller::getProperties()
{
    return this->_properties;
}




void Controller::handleKeyEvent(QString uuid , QKeyEvent *key ,  int *power, float *angle, int *nbBananas, int *nbBomb, int *nbRocket)
{
    qDebug() << " dans handleKeyEvent " << *this->nbBananas ;
    int keyAction = key->key() == Qt::Key_1 ? 1 : key->key() == Qt::Key_2 ? 2 : key->key() == Qt::Key_3 ? 3 : 0  ;

    bool isCorrectAction = ( keyAction == 1 && *nbBananas > 0) || (keyAction == 2 && *nbBomb > 0) || (keyAction ==3 && *nbRocket > 0) || (keyAction == 0) ? true : false  ;
    switch(key->key()) {
    case Qt::Key_Z:
        this->catchKeyUp(power);
        break;
    case Qt::Key_Q:
        this->catwchKeyLeft(angle);
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

void Controller::handleReleaseKeyEvent(QKeyEvent *key)
{
    switch(key->key()) {
    case Qt::Key_Q : case Qt::Key_D:
        qDebug() << "test release";
        *this->angle = 0 ;
        break ;
    }
}



void Controller::catchKeyUp(int *power)
{
    if (*this->power != 100) {
       //*this->angle = 0 ;
        *this->power += 1;
    }
}

void Controller::catchKeyDown(int *power)
{
    if(*this->power != -100) {
        *this->power -= 1;
    }
}

void Controller::catchKeyRight(float *angle)
{
    if (*this->angle != 90 )
        *this->angle = 90;
}

void Controller::catwchKeyLeft(float *angle)
{
    if (*this->angle != -90)
        *this->angle = -90;
}

void Controller::catchKeyAction( int idKey, int *nbBanana, int *nbBomb, int *nbRocket)
{
    if ((idKey == 1 && *this->nbBananas > 0) || (idKey == 2 && *this->nbBomb > 0) || (idKey == 3 && *this->nbRocket > 0))
        idKey == 1 ? *this->nbBananas-=1 : idKey == 2 ? *this->nbBomb -=1 : *this->nbRocket -=1 ;

}


void Controller::handlePressTurnLeft(bool isPushed)
{
    qDebug() << "is pushed " << isPushed ;
    if (isPushed == true ) {
        if (*this->angle != -90)
            *this->angle -= 90 ;
        this->sendMessageControl(*this->uuid , *this->angle , *this->power , 0);
    } else {
        *this->angle = 0 ;
    }
}

void Controller::handlePressTurnRight(bool isPushed) {
    qDebug() << "is pushed " << isPushed ;
    if (isPushed == true) {
        if (*this->angle != 90)
            *this->angle += 90;
    } else {
        *this->angle = 0 ;
    }
    this->sendMessageControl(*this->uuid , *this->angle , *this->power , 0);
}

void Controller::handlePressBrak(double value){
    qDebug() << "value " << value ;
    if (*power != -100)
        *power -= 1;
    this->sendMessageControl(*this->uuid , *this->angle , *this->power , 0);
}

void Controller::handlePressAccelerate(double value){
    qDebug() << "value " << value ;
    if (*power != 100)
        *power += 1;
    this->sendMessageControl(*this->uuid , *this->angle , *this->power , 0);
}

void Controller::handlePressAction1(bool isPushed) {
    if (*this->nbBananas > 0 && isPushed == true)  {
        *this->nbBananas -= 1 ;
        this->sendMessageControl(*this->uuid , *this->angle , *this->power , 1);
    }


}

void Controller::handlePressAction2(bool isPushed) {
    if (*this->nbBomb > 0 && isPushed == true) {
        *this->nbBomb -= 1 ;
        this->sendMessageControl(*this->uuid , *this->angle , *this->power , 2);}

}

void Controller::handlePressAction3(bool isPushed) {
    if (*this->nbRocket > 0 && isPushed == true) {
        *this->nbRocket -= 1 ;
        this->sendMessageControl(*this->uuid , *this->angle , *this->power , 3);
    }
}

void Controller::handlePressAction4(bool isPushed) {
    //pour l'instant rien
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

    MqttService::instance()->publish("player/register" , strJson);
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

    MqttService::instance()->publish("player/control" , strJson);
}



