#include "obstaclerect.h"

#include <QBrush>

obstacleRect::obstacleRect(QGraphicsItem *parent ):QGraphicsObject(parent)
{
}

int obstacleRect::id() const
{
    return mId;
}

QRectF obstacleRect::boundingRect() const
{
    return QRectF(-50,-50,100.,100.);
}

void obstacleRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawRect(-50,-50,100,100);
}
