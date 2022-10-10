#include "RocketGraphics.h"

qreal RocketGraphics::radius = 10;

RocketGraphics::RocketGraphics(Item *item, QGraphicsItem *parent): ItemGraphics(item, parent)
{
    this->setPos(item->getX(), item->getY());
    this->type = "Banana";
}

QRectF RocketGraphics::boundingRect() const
{
    return QRectF(-this->radius, -this->radius, this->radius*2, this->radius*2);

}

void RocketGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::white);

    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->type);

}
