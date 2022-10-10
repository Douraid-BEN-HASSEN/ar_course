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

    //valeur
    float engineCycle = 1./20; // 1 seconde / nombre de sycle
    float CDRAG = 500; // constante
    float CRR = 10;
    float GRAVITY = 9.81; // constante

    _vehicle = getPlayer()->getVehicule(); // recupere le string

    Vehicle *vehiculePlayer = Properties::getInstance()->vehicleOptions->value(_vehicle); // recupere l'objet du vehicule vehicule

    if (vehiculePlayer == nullptr) {
        return;
    }


    long double vehiculeWeight = vehiculePlayer->getWeight();

    QVector2D angleV(cos(this->_angle), -sin(this->_angle));

    long double FDrag = -CDRAG * _speedV.length() * abs(_speedV.length());
    QVector2D FDragV = angleV * FDrag;

    long double Fgr = -CRR * _speedV.length() * 0;
    QVector2D FgrV = angleV * Fgr;

    long double FGravity = vehiculeWeight * GRAVITY * sin(0);
    QVector2D FGravityV = angleV * FGravity;


    long double FTraction = ((long double)control->getPower() / 100) * vehiculePlayer->getAcceleration() * 1000; // traction
    QVector2D FTractionV = angleV * FTraction;

    _Flower = FDrag + FGravity + Fgr;
    _FlowerV = FDragV + FgrV + FGravityV;

    long double F = FTraction + FDrag + FGravity + Fgr;
    QVector2D FV = FTractionV + FDragV + FgrV + FGravityV;

//    qDebug() << "ct aero" << FcontrainteAero << "Ftraction" << Ftraction  << "_vitesse.length()" << _vitesse.length();

    long double Acceleration = F / vehiculeWeight;
    QVector2D AccelerationV = FV / vehiculeWeight;

    this->_angle += control->getAngle() * engineCycle ; // pensser a la vitesse

//    qDebug() << "Acceleration :" << Acceleration;

    // Accélération voulu



    _accelerationV = angleV * Acceleration;
//    _accelerationV = QVector2D(Acceleration, 0);

//    qDebug() << "AccelerationVector :" << _accelerationV;

    _speedV += _accelerationV * engineCycle;

    _speedV = angleV * _speedV.length();

//    _speedV *= this->_angle / 2;
//    _speedV = _accelerationV;

//    qDebug() << "Vitesse :" << _speedV;

    this->setPos(this->pos() + (this->_speedV).toPoint());
//    this->setRotation(qRadiansToDegrees(-this->_angle));
    this->setRotation(qRadiansToDegrees(0.1));
    this->setRotation(qRadiansToDegrees(0.));
//    qDebug() << "Ftot :" << ForceTot << "accel" << Accel << "_angle" <<_angle << "f" << F << "vitesse" << _vitesse;
/*
    Vehicle *vehiculePlayer = Properties::getInstance()->vehicleOptions->value(_vehicle);
    qDebug() << vehiculePlayer;
    this->_angle += control->getAngle() * engineCycle;

    float P = 1000;

    // Accélération voulu
    //QVector2D F = QVector2D(cos(this->_angle), -sin(this->_angle)) *control->getPower();
    QVector2D F = QVector2D(cos(this->_angle*(control->getPower()/100)), -sin(this->_angle)*(control->getPower()/100)) * vehiculePlayer->getMaxSpeed();
    qDebug() << vehiculePlayer->getMaxSpeed();

    // Vitesse actuel = sqrt(vx² * vy²)
    float V = sqrt(_vitesse.x()*_vitesse.x() + _vitesse.y()*_vitesse.y());
    QVector2D V_Vector(V_Vector.x()*V,V_Vector.y()*V);
    qDebug() << V_Vector.x() << V_Vector.y();
    qDebug() << "F: " << F;


    //this->_vitesse = (this->_vitesse + F) * engineCycle;
    this->_vitesse = (_vitesse + F) * engineCycle;

    this->setPos(this->getPos() +this->_vitesse.toPoint());
    this->setRotation(qRadiansToDegrees(-this->_angle));
*/
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
    qDebug() << _angle;

    QVector2D orientation = QVector2D(cos(this->_angle), -sin(this->_angle));

    painter->drawLine(QLineF(QPointF(0, 0), QPointF(cos(this->_angle), -sin(this->_angle)) * 20));
//    painter->drawLine(QLineF(QPointF(0, 0), (orientation * _Flower).toPointF()));
    painter->drawLine(QLineF(QPointF(0, 0), _FlowerV.toPointF()));


    painter->setPen(QPen(Qt::red, 3));
    painter->drawLine(QLineF(QPointF(0, 0), _accelerationV.toPointF() * 20));

    painter->setPen(QPen(Qt::green, 2));
    painter->drawLine(QLineF(QPointF(0, 0), _speedV.toPointF() * 20));

    painter->setBrush(Qt::yellow);
    painter->drawRect(QRectF(-2, -2, 4, 4));
//    painter->drawRect(QRectF(-this->heigth/2, -this->width/2, this->heigth, this->width));
//    painter->setPen(Qt::black);
//    painter->drawText(0, 0, this->_player->getPseudo());
}
