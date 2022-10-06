#include "GRocket.h"

QString GRocket::type = "rocket";
float GRocket::radius = 10;

GRocket::GRocket(QPoint pos, QGraphicsItem *parent): GItem(pos, this->type, parent)
{
    this->setProperty("type", this->type);
}

GRocket::GRocket(int x, int y, QGraphicsItem *parent): GItem(QPoint(x, y), this->type, parent)
{
    this->setProperty("type", this->type);
}

QRectF GRocket::boundingRect() const
{
    return QRectF(-this->radius, -this->radius,this->radius*2,this->radius*2);
}

void GRocket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);

    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->type);
}
