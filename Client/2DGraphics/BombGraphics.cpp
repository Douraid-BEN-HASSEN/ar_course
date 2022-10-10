#include "BombGraphics.h"

qreal BombGraphics::radius = 10;

BombGraphics::BombGraphics(Item *item, QGraphicsItem *parent): ItemGraphics(item, parent)
{
    this->setPos(item->getX(), item->getY());
    this->type = "Bomb";
}

QRectF BombGraphics::boundingRect() const
{
    return QRectF(-this->radius, -this->radius, this->radius*2, this->radius*2);

}

void BombGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( widget )
    Q_UNUSED( option )

    painter->setBrush(Qt::red);

    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->type);

}
