#include "GPlayer.h"

GPlayer::GPlayer(Player *player, QGraphicsItem *parent): QGraphicsObject{parent}
{
    this->uuid = player->getUuid();
    this->x = player->getX();
    this->y = player->getY();
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
    //painter->setBrush(Qt::red);
    //painter->drawRect(-this->heigth/2, -this->width/2, this->heigth, this->width);

    painter->setBrush(Qt::yellow);
    painter->drawEllipse(-this->heigth/2, -this->width/2, this->heigth*2, this->width*2);

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->uuid);

}
