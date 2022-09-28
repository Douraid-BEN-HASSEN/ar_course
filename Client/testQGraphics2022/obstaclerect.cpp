#include "obstaclerect.h"

#include <QBrush>

ObstacleRect::ObstacleRect(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent):QGraphicsObject(parent)
{
    //this->x = x;

}

ObstacleRect::ObstacleRect(Obstacle *obstSacle, QGraphicsItem *parent):QGraphicsObject(parent)
{
    this->x = obstSacle->x;
    this->y = obstSacle->y;
}


int ObstacleRect::id() const
{
    return mId;
}

qreal ObstacleRect::getX()
{
    return x;
}

qreal ObstacleRect::getY()
{
    return y;
}

qreal ObstacleRect::getHeigth()
{
    return heigth;
}
qreal ObstacleRect::getWidth()
{
    return width;
}


QRectF ObstacleRect::boundingRect() const
{
    return QRectF(-50,-50,100.,100.);
}

void ObstacleRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, int x, int y, int heigth, int width)
{
    painter->setBrush(Qt::blue);

    painter->drawRect(this->getX()-this->heigth/2,this->getY()-this->heigth/2,this->heigth, this->width);
}

