#include "playerGraphics3D.h"


PlayerGraphics3D::PlayerGraphics3D(Player *player, QGraphicsItem *parent): QGraphicsObject{parent}
{
    this->uuid = player->getUuid();
    //this->pseudo = player->getPseudo();
    this->x = player->getX();
    this->y = player->getY();
    //this->angle = player->getAngle();
    this->_player = player;
}

Player* PlayerGraphics3D::getPlayer()
{
    return _player;
}

QString PlayerGraphics3D::getUuid()
{
    return uuid;
}

qreal PlayerGraphics3D::getX()
{
    return x;
}

qreal PlayerGraphics3D::getY()        //painter->drawEllipse(0,0,this->heigth, this->width);
{
    return y;
}


QRectF PlayerGraphics3D::boundingRect() const
{
    //this->_player->getVehicule()->
    return QRectF(-50, -50,100.,100.);
}

void PlayerGraphics3D::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
   // painter->drawRect(-this->heigth/2, -this->width/2, this->heigth*2, this->width*2);
    painter->drawRect(boundingRect());
    this->setRotation(this->_player->getAngle());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->_player->getPseudo());

}
