#include "ObstacleGraphics.h"

#include <QBrush>

qreal ObstacleGraphics::heigth = 100;
qreal ObstacleGraphics::width = 100;
qreal ObstacleGraphics::radius = 50;

ObstacleGraphics::ObstacleGraphics(Obstacle *obstacle, QGraphicsItem *parent): QGraphicsObject(parent)
{
    this->id = obstacle->getId();
    this->x = obstacle->getX();
    this->y = obstacle->getY();
}


qreal ObstacleGraphics::getId()
{
    return id;
}

qreal ObstacleGraphics::getX()
{
    return x;
}

qreal ObstacleGraphics::getY()        //painter->drawEllipse(0,0,this->heigth, this->width);
{
    return y;
}

qreal ObstacleGraphics::getHeigth()
{
    return heigth;
}
qreal ObstacleGraphics::getWidth()
{
    return width;
}

qreal ObstacleGraphics::getRadius()
{
    return radius;
}

QRectF ObstacleGraphics::boundingRect() const
{
    return QRectF(-50, -50,100.,100.);
}

void ObstacleGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);

    if((int)this->getId() % 2 == 1){
        painter->drawRect(-this->getHeigth()/2,-this->getWidth()/2,this->heigth, this->width);
    } else {
        painter->drawEllipse(-this->getHeigth()/2,-this->getWidth()/2,this->radius*2, this->radius*2);
    }

    painter->setPen(Qt::black);
    painter->drawText(0,0,QString::number(this->getId()));

}

