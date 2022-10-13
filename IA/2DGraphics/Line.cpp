#include "Line.h"

Line::Line(QPoint p1, QPoint p2)
{
    this->_p1 = p1;
    this->_p2 = p2;
}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::blue);
    painter->drawLine(this->_p1, this->_p2);
}

//  +--------+
//  | GETTER |
//  +--------+
QPoint Line::getP1()
{
    return this->_p1;
}

QPoint Line::getP2()
{
    return this->_p2;
}

//  +--------+
//  | SETTER |
//  +--------+
void Line::setP1(QPoint p1)
{
    this->_p1 = p1;
}

void Line::setP2(QPoint p1)
{
    this->_p2 = p1;
}
