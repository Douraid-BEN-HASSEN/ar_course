#include "obstacleGraphics3D.h"
#include "Kart/Game/Properties.h"

#include <QBrush>

qreal ObstacleGraphics3D::heigth = 100;
qreal ObstacleGraphics3D::width = 100;
qreal ObstacleGraphics3D::radius = 50;

ObstacleGraphics3D::ObstacleGraphics3D(Obstacle *obstacle, QGraphicsItem *parent): QGraphicsObject(parent)
{
    this->id = obstacle->getId();
    this->x = obstacle->getX();
    this->y = obstacle->getY();
}


qreal ObstacleGraphics3D::getId()
{
    return id;
}

qreal ObstacleGraphics3D::getX()
{
    return x;
}

qreal ObstacleGraphics3D::getY()
{
    return y;
}

qreal ObstacleGraphics3D::getHeigth()
{
    return heigth;
}
qreal ObstacleGraphics3D::getWidth()
{
    return width;
}

qreal ObstacleGraphics3D::getRadius()
{
    return radius;
}

QRectF ObstacleGraphics3D::boundingRect() const
{
    if((int)this->id % 2 == 1){
        return QRectF(-this->heigth/2, -this->width/2,this->heigth,this->width);
    } else {
        return QRectF(-this->heigth/2, -this->width/2,this->radius*2,this->radius*2);
    }
}

void ObstacleGraphics3D::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

