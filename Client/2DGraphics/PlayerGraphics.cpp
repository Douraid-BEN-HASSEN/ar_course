#include "PlayerGraphics.h"
#include <Kart/Game/Vehicle.h>
#include <Kart/Game/Properties.h>

PlayerGraphics::PlayerGraphics(Player *player, QGraphicsItem *parent): QGraphicsObject{parent}
{
    this->uuid = player->getUuid();
    //this->pseudo = player->getPseudo();
    this->x = player->getX();
    this->y = player->getY();
    this->_player = player;
}

Player* PlayerGraphics::getPlayer()
{
    return _player;
}

QString PlayerGraphics::getUuid()
{
    return uuid;
}

qreal PlayerGraphics::getX()
{
    return x;
}

qreal PlayerGraphics::getY()        //painter->drawEllipse(0,0,this->heigth, this->width);
{
    return y;
}

qreal PlayerGraphics::getHeigth()
{
    return heigth;
}
qreal PlayerGraphics::getWidth()
{
    return width;
}

void PlayerGraphics::updatePlayer(Player *player) {
    this->_player = player;
    this->setPos(player->getX(), player->getY());
    qDebug() << player->getAngle();
    this->setRotation(qRadiansToDegrees(-player->getAngle()));

    Vehicle *veh = Properties::getInstance()->vehicleOptions->value(player->getVehicule());
    if (veh != nullptr) {
        this->heigth = veh->getHeight();
        this->width = veh->getWidth();
    }
}


QRectF PlayerGraphics::boundingRect() const
{
    return QRectF(-this->heigth/2, -this->width/2,this->heigth,this->width);
}

void PlayerGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    painter->drawRect(boundingRect());
    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->_player->getPseudo());

}
