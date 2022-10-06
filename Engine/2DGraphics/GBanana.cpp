#include "GBanana.h"

QString GBanana::type = "GBanana";

GBanana::GBanana(QPoint pos, QGraphicsItem *parent): GItem(pos, parent)
{
    this->setProperty("type", this->type);
}

GBanana::GBanana(int x, int y, QGraphicsItem *parent): GItem(QPoint(x, y), parent)
{
    this->setProperty("type", this->type);
}

QRectF GBanana::boundingRect() const
{
    return QRectF(-this->heigth, -this->width,this->heigth*2,this->width*2);
}

void GBanana::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);

    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->type);
}
