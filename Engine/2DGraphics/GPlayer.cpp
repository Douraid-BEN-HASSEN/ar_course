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

QRectF GPlayer::boundingRect() const
{
    return QRectF(-this->heigth/2, -this->width/2, this->heigth, this->width);
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
    this->_vitesse = vectorSpeed;
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

    float engineCycle = 1./20; // 1 seconde / nombre de sycle

    this->_angle += control->getAngle() * engineCycle;

    float P = 1000;

    // Accélération voulu
    QVector2D F = QVector2D(cos(this->_angle), -sin(this->_angle)) *control->getPower();

    // Vitesse actuel = sqrt(vx² * vy²)
    float V = sqrt(_vitesse.x()*_vitesse.x() + _vitesse.y()*_vitesse.y());

    this->_vitesse = (this->_vitesse + F) * engineCycle;

    this->setPos(this->getPos() +this->_vitesse.toPoint());
    this->setRotation(qRadiansToDegrees(-this->_angle));
}

void GPlayer::hit()
{
    this->_vitesse = QVector2D(0, 0);
    this->_stunt = 25;
}

void GPlayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    painter->drawRect(boundingRect());
    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->_player->getPseudo());
}

// void GPlayer::setPos(QPoint a)
// {
//     qDebug("connard");
// }
