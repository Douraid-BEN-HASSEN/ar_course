#include "GRocket.h"

QString GRocket::type = "GBanana";

GRocket::GRocket(Item *item, QGraphicsItem *parent): GItem(item, parent)
{
    this->setProperty("type", this->type);
}

QRectF GRocket::boundingRect() const
{
    return QRectF(-this->heigth, -this->width,this->heigth*2,this->width*2);
}

void GRocket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);

    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->type);
}
