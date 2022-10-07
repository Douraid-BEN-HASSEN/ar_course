#include "BombGraphics.h"

BombGraphics::BombGraphics(Item *item, QGraphicsItem *parent): ItemGraphics(item, parent)
{
    this->setPos(item->getX(), item->getY());
    this->type = "Bomb";
}

QRectF BombGraphics::boundingRect() const
{
    return QRectF(-this->heigth, -this->width,this->heigth*2,this->width*2);

}

void BombGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);

    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->type);

}
