#include "GRocket.h"

QString GRocket::type = "rocket";
float GRocket::radius = 10;
float GRocket::speed = 150;

GRocket::GRocket(QPoint pos, float angle, QGraphicsItem *parent): GItem(pos, this->type, parent)
{
    this->setProperty("type", this->type);
    this->_angle = angle;
}

GRocket::GRocket(int x, int y, float angle, QGraphicsItem *parent): GItem(QPoint(x, y), this->type, parent)
{
    this->setProperty("type", this->type);
    this->_angle = angle;
}

void GRocket::update()
{
    float engineCycle = 1./20; // 1 seconde / nombre de sycle

    QVector2D vector = QVector2D(cos(this->_angle), -sin(this->_angle)) * this->speed * engineCycle;

    this->setPos(this->pos().toPoint() + vector.toPoint());
    this->setRotation(qRadiansToDegrees(-this->_angle));
}

QRectF GRocket::boundingRect() const
{
    return QRectF(-this->radius, -this->radius, this->radius*2, this->radius*2);
}

void GRocket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::gray);

    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->type);
}
