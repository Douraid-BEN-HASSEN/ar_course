#include "GBanana.h"

QString GBanana::type = "banana";
float GBanana::radius = 10;

GBanana::GBanana(QPoint pos, QGraphicsItem *parent): GItem(pos, this->type, parent)
{
    this->setProperty("type", this->type);
}

GBanana::GBanana(int x, int y, QGraphicsItem *parent): GItem(QPoint(x, y), this->type, parent)
{
    this->setProperty("type", this->type);
}


void GBanana::update()
{
}

QRectF GBanana::boundingRect() const
{
    return QRectF(-this->radius, -this->radius,this->radius*2,this->radius*2);
}

void GBanana::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);

    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->type);
}
