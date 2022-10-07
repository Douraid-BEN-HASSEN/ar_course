#include "GBomb.h"

QString GBomb::type = "bomb";
float GBomb::radius = 10;

GBomb::GBomb(QPoint pos, float angle, QGraphicsItem *parent): GItem(pos, this->type, parent)
{
    this->type = type;

    this->_angle = angle;
    this->setProperty("type", this->type);
}

GBomb::GBomb(int x, int y, float angle, QGraphicsItem *parent): GItem(QPoint(x, y), this->type, parent)
{
    this->_angle = angle;
    this->setProperty("type", this->type);
}

void GBomb::update()
{
    if (_distanceDrop <= 0) {
        return;
    }

    float engineCycle = 1./20; // 1 seconde / nombre de sycle

    QVector2D speed = QVector2D(cos(this->_angle), -sin(this->_angle)) * 150 * engineCycle;

    _distanceDrop -= speed.length();

    qDebug() << _distanceDrop << " " <<  speed.length();

    this->setPos(this->pos().toPoint() + speed.toPoint());
    this->setRotation(qRadiansToDegrees(-this->_angle));
}


QRectF GBomb::boundingRect() const
{
    return QRectF(-this->radius, -this->radius,this->radius*2,this->radius*2);
}

void GBomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);

    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->type);
}
