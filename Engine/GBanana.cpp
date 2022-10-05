#include "GBanana.h"
QString GBanana::type = "GBanana";
GBanana::GBanana(Item *banana, QGraphicsItem *parent):QGraphicsObject(parent)
{
    this->setProperty("type", this->type);

    this->banana = banana;
    this->x = banana->getX();
    this->y = banana->getY();
    this->radiusBanana = getRadius();
}

Item *GBanana::getItem()
{
    return this->banana;
}


qreal GBanana::getX()
{
    return x;
}

qreal GBanana::getY()
{
    return y;
}

qreal GBanana::getRadius()
{
    return radiusBanana;
}

QRectF GBanana::boundingRect() const
{
    return QRectF(-this->radiusBanana, -this->radiusBanana,this->radiusBanana*2,this->radiusBanana*2);

}

void GBanana::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    //painter->drawEllipse(-this->getRadius(),-this->getRadius(),this->radius*2, this->radius*2);
    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);


}
