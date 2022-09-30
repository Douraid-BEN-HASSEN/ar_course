#include "GObstacle.h"

qreal GObstacle::heigth = 100;
qreal GObstacle::width = 100;
qreal GObstacle::radius = 50;

GObstacle::GObstacle(Obstacle *obstacle, QGraphicsItem *parent): QGraphicsObject(parent)
{
    this->id = obstacle->getId();
    this->x = obstacle->getX();
    this->y = obstacle->getY();
}


qreal GObstacle::getId()
{
    return id;
}

qreal GObstacle::getX()
{
    return x;
}

qreal GObstacle::getY()
{
    return y;
}

qreal GObstacle::getHeigth()
{
    return heigth;
}
qreal GObstacle::getWidth()
{
    return width;
}

qreal GObstacle::getRadius()
{
    return radius;
}

QRectF GObstacle::boundingRect() const
{
    return QRectF(-50, -50,100.,100.);
}

void GObstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
