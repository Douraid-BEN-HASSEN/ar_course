#include "GBanana.h"

QString GBanana::type = "banana";
float GBanana::radius = 10;

GBanana::GBanana(QPoint pos, float angle, QGraphicsItem *parent): GItem(pos, angle, this->type, parent)
{
    this->setProperty("type", this->type);
    this->item->setStatus("placed");
}

GBanana::GBanana(int x, int y, float angle, QGraphicsItem *parent): GItem(QPoint(x, y), angle, this->type, parent)
{
    this->setProperty("type", this->type);
    this->item->setStatus("placed");
}


void GBanana::update()
{
}

QRectF GBanana::boundingRect() const
{
    return QRectF(-this->radius, -this->radius, this->radius*2, this->radius*2);
}

void GBanana::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);

    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->type);
}
