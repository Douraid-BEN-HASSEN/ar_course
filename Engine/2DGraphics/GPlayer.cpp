#include "GPlayer.h"

QString GPlayer::type = "GPlayer";

GPlayer::GPlayer(Player *player, QGraphicsItem *parent): QGraphicsObject{parent}
{
    this->setProperty("type", this->type);

    this->uuid = player->getUuid();
    this->setPos(player->getPosition());
    this->_player = player;

    this->_nBanane = 0;
    this->_nBomb = 0;
    this->_nRocket = 0;

    this->_bananaCooldown = 0;
    this->_bombCooldown = 0;
    this->_rocketCooldown = 0;
}

QPoint GPlayer::getPos()
{
    return QPoint(this->x(), this->y());
}

float GPlayer::getAngle()
{
    return _angle;
}

int GPlayer::getBananaCooldown()
{
    return this->_bananaCooldown;
}

int GPlayer::getBombCooldown()
{
    return this->_bombCooldown;
}

int GPlayer::getRocketCooldown()
{
    return this->_rocketCooldown;
}

int GPlayer::getnBanana()
{
    return this->_nBanane;
}

int GPlayer::getnRocket()
{
    return this->_nRocket;
}

int GPlayer::getnBomb()
{
    return this->_nBomb;
}

Player* GPlayer::getPlayer()
{
    return _player;
}

QString GPlayer::className()
{
    return "className";
}

QString GPlayer::getUuid()
{
    return uuid;
}

void GPlayer::setHeigth(int heigth) {
    this->heigth = heigth;
}

void GPlayer::setWidth(int width) {
    this->width = width;
}

void GPlayer::setAngle(float angle) {

    while (angle > 0) {
        angle -= 2 * M_PI;
        //qDegreesToRadians(angle);
    }

    while (angle < -M_PI) {
        angle += 2 * M_PI;
        //qDegreesToRadians(angle);
    }

    _angle = angle;
}

void GPlayer::setBananaCooldown(int pBananaCooldown)
{
    this->_bananaCooldown = pBananaCooldown;
}

void GPlayer::setBombCooldown(int pBombCooldown)
{
    this->_bombCooldown = pBombCooldown;
}

void GPlayer::setRocketCooldown(int pRockerCooldown)
{
    this->_rocketCooldown = pRockerCooldown;
}

void GPlayer::setnBanana(int pnBanana)
{
    this->_nBanane = pnBanana;
}

void GPlayer::setnBomb(int pnBomb)
{
    this->_nBomb = pnBomb;
}

void GPlayer::setnRocket(int pnRocket)
{
    this->_nRocket = pnRocket;
}

void GPlayer::setVitesse(QVector2D vectorSpeed)
{
    this->_speedV = vectorSpeed;
}

void GPlayer::update(Control *control)
{
    if (!control) {
        return;
    }

    if (_stunt > 0) {
        _stunt--;
        return;
    }

    if(_speed==0){
        control->setAngle(0.0);
    }

    //Constantes et valeurs
    float engineCycle = 1./20; // 1 seconde / nombre de sycle
    float CDRAG = 500; // constante
    float CRR = 10;
    float GRAVITY = 9.81; // constante

    //recupere le nom du vehicule
    _vehicle = getPlayer()->getVehicule(); // recupere le string

    //recupere l'objet
    Vehicle *vehiculePlayer = Properties::getInstance()->vehicleOptions->value(_vehicle); // recupere l'objet du vehicule vehicule

    if (vehiculePlayer == nullptr) {
        return;
    }

    _vehiculeWeight = vehiculePlayer->getWeight(); // poid du véhicule
    float FDrag = 0.0;
    QVector2D angleV(cos(this->_angle), -sin(this->_angle));


    qDebug() << "SpeedV :" << _speedV.length() * 1 / engineCycle;

    //Force drag
    if(_speed>0){
        FDrag = -CDRAG * _speedV.length() * abs(_speedV.length());
    }else{
        FDrag = CDRAG * _speedV.length() * abs(_speedV.length());
    }
    QVector2D FDragV = angleV * FDrag;

    // force gravité
    float Fgr;
    if(_speed>0){
        Fgr = -CRR * _speedV.length() * 0;
    }else{
        Fgr = -(-CRR * _speedV.length() * 0);
    }
    QVector2D FgrV = angleV * Fgr;

    float FGravity = _vehiculeWeight * GRAVITY * sin(0);
    QVector2D FGravityV = angleV * FGravity;

    float power = ((float)control->getPower() / 100);



    float FTraction = power * vehiculePlayer->getAcceleration() * 1000; // traction
    QVector2D FTractionV = angleV * FTraction;



    _Flower = FDrag + FGravity + Fgr;
    _FlowerV = FDragV + FgrV + FGravityV;

    qDebug() << "vmax" << vehiculePlayer->getMaxSpeed() << "vmax/engine" << vehiculePlayer->getMaxSpeed() * engineCycle;

    /* limitateur de speed */
    if (_speedV.length() >= vehiculePlayer->getMaxSpeed() * engineCycle) {

        if (FTractionV.length() > _FlowerV.length()) {
            FTractionV = _FlowerV * -1;
        }
    }

    float F = FTraction + FDrag + FGravity + Fgr;
    float Acceleration = F / _vehiculeWeight;
    _speed += Acceleration * engineCycle;


    QVector2D FV = FTractionV + FDragV + FgrV + FGravityV;
    QVector2D AccelerationV = FV / _vehiculeWeight;
    _accelerationV = AccelerationV;
    _speedV += _accelerationV * engineCycle;

    //rajout du steering
    float angleControl = control->getAngle();

    if (vehiculePlayer->getSteeringAngle() == -1) {
        qDebug() << "steering -1";

    } else if (angleControl > vehiculePlayer->getSteeringAngle()){
         angleControl = vehiculePlayer->getSteeringAngle();
         qDebug() << "angleControl > vehiculePlayer->getSteeringAngle()";

    } else if (abs(angleControl) > vehiculePlayer->getSteeringAngle())  {
        angleControl = -vehiculePlayer->getSteeringAngle();
        qDebug() << "abs (angleControl) > vehiculePlayer->getSteeringAngle()";
    }

    //qDebug() << "angleControl" << angleControl;
    //qDebug() << "angleVehicule" <<vehiculePlayer->getSteeringAngle();
    //this->_angle = (_angle + angleControl * engineCycle); // pensser a la vitesse

    this->setAngle(_angle + angleControl * engineCycle); // pensser a la vitesse


    qDebug() << "Abstract speed " << _speed;
    if (_speed >= 0){
        _speedV = angleV * _speedV.length();
    }else{
        _speedV = -(angleV * _speedV.length())/1.1;
    }



    float a = QLineF(QPointF(0, 0), _speedV.toPointF()).angle();

//    qDebug() << a;
//    qDebug() << qRadiansToDegrees(_angle);
    // a modifier


    if (_speedV.length() <= 0.5 && _accelerationV.length() < 0.1) {
        _speedV *= 0;
        _speed = 0;
    }
//    if (_speed <= 2 && Acceleration < 0.2 && Acceleration > -0.2) {
//        _speed *= 0;
//    }

    this->setPos(this->pos() + (this->_speedV).toPointF());
    this->setRotation(qRadiansToDegrees(-this->_angle));

//    qDebug() << "All Drag:" << _FlowerV.length();
//    qDebug() << "Speed :" << _speedV.length();
//    qDebug() << "Speed m/s:" << _speedV.length() * 1 / engineCycle ;
//    qDebug() << "Acceleration :" << _accelerationV.length();
    qDebug() << "angle" << _angle;
}

void GPlayer::hit()
{
    this->_speedV = QVector2D(0, 0);
    this->_stunt = 25;
}

QTime GPlayer::getTime()
{
    return timeLaps;
}

void GPlayer::setTime(QTime time)
{
    timeLaps = time;
    qDebug() << timeLaps;
    emit stateUpdated();
}

QString GPlayer::getState()
{
    return state;
}

void GPlayer::setState(QString state)
{
    this->state = state;
    emit stateUpdated();
}

QPainterPath GPlayer::shape() const
{
    QPainterPath path;
    if (this->boundingRect().isNull())
        return path;

    path.addRect(QRectF(-this->heigth/2, -this->width/2, this->heigth, this->width));
    return path;
}

QRectF GPlayer::boundingRect() const
{
    return QRectF(-1000, -1000, 2000, 2000);
}

void GPlayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QVector2D orientation = QVector2D(cos(this->_angle), -sin(this->_angle));

    painter->drawLine(QLineF(0, 0, 20, 0));

    painter->setPen(QPen(Qt::yellow, 2));
    painter->drawLine(QLineF(0, 0, (_speed >= 0 ? _FlowerV.length() : -_FlowerV.length()) / this->_vehiculeWeight, 0));

    painter->setPen(QPen(Qt::red, 3));
    painter->drawLine(QLineF(0, 0, _speed >= 0 ? _accelerationV.length() * 20 : -_accelerationV.length() * 20, 0));

    painter->setPen(QPen(Qt::green, 2));
    painter->drawLine(QLineF(0, 0, _speed >= 0 ? _speedV.length() * 20 : -_speedV.length() * 20, 0));

//    painter->setBrush(Qt::yellow);
//    painter->drawRect(QRectF(-this->heigth/2, -this->width/2, this->heigth, this->width));
    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->_player->getPseudo());
}
