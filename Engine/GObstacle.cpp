#include "GObstacle.h"

#include <QBrush>

qreal GObstacle::heigth = 100;
qreal GObstacle::width = 100;
qreal GObstacle::radius = 50;

GObstacle::GObstacle(Obstacle *obstacle, QGraphicsItem *parent): QGraphicsObject(parent)
{
    this->id = obstacle->getId();
    this->x = obstacle->getX();
    this->y = obstacle->getY();
    //this->heigth = Properties::getInstance()->getRectangleWidth();
    //this->width = Properties::getInstance()->getRectangleHeight();
}


qreal GObstacle::getId()
{
    return id;
}

qreal GObstacle::getX()
{
    return x;
}

qreal GObstacle::getY()        //painter->drawEllipse(0,0,this->heigth, this->width);
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
    if((int)this->id % 2 == 1){
        return QRectF(-this->heigth/2, -this->width/2,this->heigth,this->width);
    } else {
        return QRectF(-this->heigth/2, -this->width/2,this->radius*2,this->radius*2);
    }


}

void GObstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);

    if((int)this->getId() % 2 == 1){
        painter->drawRect(boundingRect());
    } else {
         painter->drawEllipse(boundingRect());
    }

    painter->setPen(Qt::black);
    painter->drawText(0,0,QString::number(this->getId()));

}
