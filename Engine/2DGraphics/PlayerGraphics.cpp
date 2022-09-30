#include "PlayerGraphics.h"

PlayerGraphics::PlayerGraphics(Player *player, QGraphicsItem *parent): QGraphicsObject{parent}
{
    this->uuid = player->getUuid();
    this->x = player->getX();
    this->y = player->getY();
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
    return QRectF(-50, -50,100.,100.);
}

void PlayerGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawRect(-this->heigth/2, -this->width/2, this->heigth, this->width);

    painter->setBrush(Qt::yellow);
    painter->drawEllipse(-this->heigth/2, -this->width/2, this->heigth*2, this->width*2);

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->uuid);

}
