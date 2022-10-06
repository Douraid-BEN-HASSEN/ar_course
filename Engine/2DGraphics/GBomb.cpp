#include "GBomb.h"

QString GBomb::type = "GBomb";

GBomb::GBomb(QPoint pos, QGraphicsItem *parent): GItem(pos, parent)
{
    this->setProperty("type", this->type);
}

GBomb::GBomb(int x, int y, QGraphicsItem *parent): GItem(QPoint(x, y), parent)
{
    this->setProperty("type", this->type);
}


QRectF GBomb::boundingRect() const
{
    return QRectF(-this->heigth, -this->width,this->heigth*2,this->width*2);
}

void GBomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);

    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->type);
}
