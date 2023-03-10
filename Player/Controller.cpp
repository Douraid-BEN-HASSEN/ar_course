#include "Controller.h"

#include <QtMath>

Controller::Controller(QObject *parent): QObject{parent}
{
    qDebug() << "Controller::Controller" ;
    this->_properties = Properties::getInstance();
    this->createGamepad();

    this->uuid = QUuid::createUuid().toString();
    this->power = 0 ;
    this->angle = 0.0 ;
    this->nbBananas = 0 ;
    this->nbBomb = 0 ;
    this->nbRocket = 0 ;
    this->_properties = Properties::getInstance();

    connect(Properties::getInstance(), SIGNAL(updated()), this, SLOT(onRunFind()));
    connect(GameMode::getInstance(), SIGNAL(updated()), this, SLOT(onGamemodeFind()));
}

void Controller::onRunFind() {
    qDebug() << "Controller::onRunFind()" ;


    this->nbTurn = Properties::getInstance()->getLaps() ;
    this->nbTeam = Properties::getInstance()->getTeam() ;
    this->vehicleOptions = Properties::getInstance()->vehicleOptions;
    emit this->runFind() ;
}

void Controller::onGamemodeFind()
{
    qDebug() << "Controller::onGamemodeFind()" ;
    Player *player = GameMode::getInstance()->_players->value(this->uuid);

    if (!player)
        return;

    this->nbBananas = player->getItems()->value("banana") ;
    this->nbBomb = player->getItems()->value("bomb") ;
    this->nbRocket = player->getItems()->value("rocket");
    emit this->gamemodeFind() ;
}

void Controller::createGamepad(){
    qDebug() << "Controller::createGamepad" ;
    QLoggingCategory::setFilterRules(QStringLiteral("qt.gamepad.debug=true"));
    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    this->gamepad = new QGamepad(*gamepads.begin(), this);

    //Connect
    connect(gamepad, SIGNAL(buttonL1Changed(bool)), this, SLOT(handlePressTurnLeft(bool)));
    connect(gamepad, SIGNAL(buttonR1Changed(bool)), this, SLOT(handlePressTurnRight(bool)));
    connect(gamepad,SIGNAL(buttonL2Changed(double)), this, SLOT(handlePressBreake(double)));
    connect(gamepad,SIGNAL(buttonR2Changed(double)), this, SLOT(handlePressAccelerate(double)));
    connect(gamepad,SIGNAL(buttonAChanged(bool)), this, SLOT(handlePressAction1(bool)));
    connect(gamepad,SIGNAL(buttonBChanged(bool)), this, SLOT(handlePressAction2(bool)));
    connect(gamepad,SIGNAL(buttonXChanged(bool)), this, SLOT(handlePressAction3(bool)));
    connect(gamepad,SIGNAL(buttonYChanged(bool)), this, SLOT(handlePressAction4(bool)));
    connect(gamepad, SIGNAL(axisLeftXChanged(double)) , this , SLOT(handleTurnLeftJoystick(double)));

}

QGamepad *Controller::getGamepad()
{
    return this->gamepad ;
}

void Controller::setUuid(QString uuid)
{
    this->uuid = uuid ;
}

Properties* Controller::getProperties()
{
    qDebug() << "Controller::getProperties()" ;
    return this->_properties;
}

QMap<QString, Vehicle *> *Controller::getVehicleOptions() const
{
    return vehicleOptions;
}

void Controller::handleKeyEvent(QKeyEvent *key )
{
    qDebug() << "Controller::handleKeyEvent() " << Qt::Key(key->key()) ;
    int keyAction = key->key() == Qt::Key_1 ? 1 : key->key() == Qt::Key_2 ? 2 : key->key() == Qt::Key_3 ? 3 : 0  ;
    bool isCorrectAction = ( keyAction == 1 && nbBananas > 0) || (keyAction == 2 && nbBomb > 0) || (keyAction ==3 && nbRocket > 0) || (keyAction == 0) ? true : false  ;
    switch(key->key()) {
    case Qt::Key_Z:
        this->catchKeyUp();
        break;
    case Qt::Key_Q:
        this->catchKeyLeft();
        break ;
    case Qt::Key_S:
        this->catchKeyDown();
        break ;
    case Qt::Key_D:
        this->catchKeyRight();
        break ;
    case Qt::Key_1:
        keyAction = 1 ;
        this->catchKeyAction(1 );
        break ;
    case Qt::Key_2:
        keyAction = 2 ;
        this->catchKeyAction(2 );
        break ;
    case Qt::Key_3:
        keyAction = 3 ;
        this->catchKeyAction(3 );
        break ;
    case Qt::Key_4:
        keyAction = 4 ;
        this->catchKeyAction(4 );
        break ;
    case Qt::Key_Ampersand :
        keyAction = 1 ;
        this->catchKeyAction(1 );
        break ;
    case Qt::Key_Eacute :
        keyAction = 2 ;
        this->catchKeyAction(2 );
        break ;
    case Qt::Key_QuoteDbl :
        keyAction = 3 ;
        this->catchKeyAction(3 );
        break ;
    case Qt::Key_Apostrophe :
        keyAction = 4 ;
        this->catchKeyAction(4 );
        break ;
    }
    if (isCorrectAction == true )
        this->sendMessageControl( keyAction);
}

void Controller::handleReleaseKeyEvent(QKeyEvent *key)
{
    qDebug() << "Controller::handleReleaseKeyEvent()" ;
    switch(key->key()) {
    case Qt::Key_Q :
        this->angle = 0 ;
        this->sendMessageControl(0);
        break ;
    case Qt::Key_D:
        this->angle = 0 ;
        this->sendMessageControl(0);
        break ;
    case Qt::Key_Z :
        this->power = 0 ;
        this->sendMessageControl( 0);
        break ;
    case Qt::Key_S :
        this->power = 0 ;
        this->sendMessageControl( 0);
        break ;
    }
}



void Controller::catchKeyUp()
{
    qDebug() << "Controller::catchKeyUp()" ;
    this->power = 100;
}

void Controller::catchKeyDown()
{
    qDebug() << "Controller::catchKeyDown()" ;
    this->power = -100;
}

void Controller::catchKeyRight()
{
    qDebug() << "Controller::catchKeyRight()";
    if (this->angle != -90 )
        this->angle = -90;
}

void Controller::catchKeyLeft()
{
    qDebug() << "Controller::catchKeyLeft()";
    if (this->angle != +90)
        this->angle = +90;
}

void Controller::catchKeyAction( int idKey)
{
    qDebug() << "Controller::catchKeyAction()";
    if ((idKey == 1 && this->nbBananas > 0) || (idKey == 2 && this->nbBomb > 0) || (idKey == 3 && this->nbRocket > 0))
        idKey == 1 ? this->nbBananas-=1 : idKey == 2 ? this->nbBomb -=1 : this->nbRocket -=1 ;
}


void Controller::handlePressTurnLeft(bool isPushed)
{
    qDebug() << "Controller::handlePressTurnLeft()" ;
    if (this->controllerType == "controller") {
        if (isPushed == true ) {
            if (this->angle != -90)
                this->angle -= 90;
            this->sendMessageControl( 0);
        } else
            this->angle = 0 ;
    }
}

void Controller::handlePressTurnRight(bool isPushed) {
    qDebug() << "Controller::handlePressTurnRight()" ;
    if (this->controllerType == "controller") {
        if (isPushed == true) {
            if (this->angle != 90)
                this->angle += 90;
            this->sendMessageControl( 0);
        } else
            this->angle = 0 ;
    }
}

void Controller::handlePressBreake(double value){
    qDebug() << "Controller::handlePresseBreake()";
    if (this->controllerType == "controller") {
        if (value > 0 ) {
            this->power = value * - 100 ;
        } else {
            power = 0 ;
        }
        this->sendMessageControl( 0);
    }
}

void Controller::handlePressAccelerate(double value){
    qDebug() << "Controller::handlePressAccelerate()" << value;

    if (this->controllerType == "controller") {
        if (value > 0) {
            this->power = value * 100 ;
        } else
            power = 0 ;

        this->sendMessageControl( 0);
    }
}

void Controller::handlePressAction1(bool isPushed) {
    if (this->controllerType == "controller") {
        qDebug() << "Controller::handlePressAction1()";
        if (this->nbBananas > 0 && isPushed == true)  {
            this->nbBananas -= 1 ;
            this->sendMessageControl(1);
        }
    }
}

void Controller::handlePressAction2(bool isPushed) {
    if (this->controllerType == "controller") {
        qDebug() << "Controller::handlePressAction2()";
        if (this->nbBomb > 0 && isPushed == true) {
            this->nbBomb -= 1 ;
            this->sendMessageControl( 2);}
    }
}

void Controller::handlePressAction3(bool isPushed) {
    qDebug() << "Controller::handlePressAction3()";
    if (this->controllerType == "controller") {
        if (this->nbRocket > 0 && isPushed == true) {
            this->nbRocket -= 1 ;
            this->sendMessageControl( 3);
        }
    }
}

void Controller::handlePressAction4(bool isPushed) {
    qDebug() << "Controller::handlePressAction4()";
}

void Controller::handleTurnLeftJoystick(double value)
{
    qDebug() << "Controller::handleTurnRightJoystick()" << value ;
    if (this->controllerType == "controller") {
        if (value != 0) {
            if (value < 0 ) { //Turn left
                this->angle = -1.0 * (value * 90);
                this->sendMessageControl( 0);
                this->angle = 0 ;
            } else if (value > 0) { //Turn right
                this->angle = -(value*90);
                this->sendMessageControl( 0);
                this->angle = 0 ;
            }
        }
        else {
            this->angle = 0 ;
        }

    }
}

void Controller::setControllerType(QString controllerType)
{
    this->controllerType = controllerType ;
}

void Controller::sendMessageRegister( QString pseudo, QString controller, QString vehicle, QString team)
{
    qDebug() << "Controller::sendMessageRegister()" ;
    QJsonObject messageJsonObject ;
    messageJsonObject.insert("uuid" , this->uuid);
    messageJsonObject.insert("pseudo" , pseudo);
    messageJsonObject.insert("controller" , controller);
    messageJsonObject.insert("vehicle" , vehicle);
    messageJsonObject.insert("team" , team == "No team" ? "null" : team);
    QJsonDocument doc(messageJsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    MqttService::instance()->publish("player/register" , strJson);
}

void Controller::sendMessageControl(int keyAction)
{
    qDebug() << "Controller::sendMessageControl()" ;
    QJsonObject messageJsonObject ;
    messageJsonObject.insert("uuid" , this->uuid);
    messageJsonObject.insert("angle" , qDegreesToRadians(double(this->angle)) );
    messageJsonObject.insert("power" , this->power);
    QJsonObject messageJsonButtonsObject ;
    messageJsonButtonsObject.insert("banana" , keyAction == 1 ? true : false);
    messageJsonButtonsObject.insert("bomb" , keyAction == 2 ? true : false);
    messageJsonButtonsObject.insert("rocket" , keyAction == 3 ? true : false);
    messageJsonObject.insert("buttons" , messageJsonButtonsObject);
    QJsonDocument doc(messageJsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    MqttService::instance()->publish("player/control" , strJson);
}

QString Controller::getUuid()
{
    return this->uuid ;
}

int Controller::getNbBananas(){
    return this->nbBananas ;
}

int Controller::getNbBombs(){
    return this->nbBomb ;
}

int Controller::getNbRocket(){
    return this->nbRocket;
}

void Controller::setNbBananas(int n) {
    this->nbBananas = n ;
}
void Controller::setNbBombs(int n) {
    this->nbBomb = n ;
}

void Controller::setNbRocket(int n) {
    this->nbRocket = n ;
}

int Controller::getNbTurn(){
    return this->nbTurn ;
}
int Controller::getNbTeams() {
    return this->nbTeam  ;
}

float Controller::getAngle(){
    return this->angle ;
}

int Controller::getPower() {
    return this->power ;
}
