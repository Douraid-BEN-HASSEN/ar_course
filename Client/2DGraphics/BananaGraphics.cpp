#include "BananaGraphics.h"

BananaGraphics::BananaGraphics(Item *item, QGraphicsItem *parent): ItemGraphics(item, parent)
{
    this->setPos(item->getX(), item->getY());
    this->type = "Banana";
}

QRectF BananaGraphics::boundingRect() const
{
    return QRectF(-this->heigth, -this->width,this->heigth*2,this->width*2);

}

void BananaGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);

    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->type);

}
