#include "GPlayer.h"

GPlayer::GPlayer(Player *player, QGraphicsItem *parent): QGraphicsObject{parent}
{
    this->uuid = player->getUuid();
    this->x = player->getX();
    this->y = player->getY();
    this->_player = player;
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

qreal GPlayer::getX()
{
    return x;
}

qreal GPlayer::getY()        //painter->drawEllipse(0,0,this->heigth, this->width);
{
    return y;
}


QRectF GPlayer::boundingRect() const
{
    return QRectF(-50, -50,100.,100.);
}

void GPlayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    painter->drawRect(boundingRect());
    this->setRotation(this->_player->getAngle());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->_player->getPseudo());
}
