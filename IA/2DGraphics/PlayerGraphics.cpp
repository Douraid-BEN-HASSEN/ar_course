#include "PlayerGraphics.h"


PlayerGraphics::PlayerGraphics(Player *player, QGraphicsItem *parent): QGraphicsObject{parent}
{
    this->uuid = player->getUuid();
    //this->pseudo = player->getPseudo();
    this->x = player->getX();
    this->y = player->getY();
    //this->angle = player->getAngle();
    this->_player = player;
}

void PlayerGraphics::updatePlayer(Player *player) {
    this->_player = player;
    // this->setPos(player->getX(), player->getY());
    this->setRotation(qRadiansToDegrees(-player->getAngle()));
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


QRectF PlayerGraphics::boundingRect() const
{
    return QRectF(-50, -50, 100., 100.);
}

void PlayerGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawRect(50, 0, 10, 10);
    painter->setBrush(Qt::yellow);
    painter->drawRect(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->_player->getPseudo());

}
