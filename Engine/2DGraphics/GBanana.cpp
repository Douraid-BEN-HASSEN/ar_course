#include "GBanana.h"

QString GBanana::type = "banana";
float GBanana::radius = 10;

GBanana::GBanana(QPoint pos, QGraphicsItem *parent): GItem(pos, this->type, parent)
{
    this->setProperty("type", this->type);
}

GBanana::GBanana(int x, int y, QGraphicsItem *parent): GItem(QPoint(x, y), this->type, parent)
{
    this->setProperty("type", this->type);
}


void GBanana::update()
{
//    if (!control) {
//        return;
//    }

//    if (_stunt > 0) {
//        _stunt--;
//        return;
//    }

//    float engineCycle = 1./20; // 1 seconde / nombre de sycle

//    this->_angle += -control->getAngle() * engineCycle;

//    float P = 1000;

//    // Accélération voulu
//    QVector2D F = QVector2D(cos(this->_angle), -sin(this->_angle)) *control->getPower();

//    // Vitesse actuel = sqrt(vx² * vy²)
//    float V = sqrt(_vitesse.x()*_vitesse.x() + _vitesse.y()*_vitesse.y());

//    this->_vitesse = (this->_vitesse + F) * engineCycle;

//    qDebug() << _vitesse;

//    this->setPos(this->getPos() +this->_vitesse.toPoint());
//    this->setRotation(qRadiansToDegrees(-this->_angle));

}

QRectF GBanana::boundingRect() const
{
    return QRectF(-this->radius, -this->radius,this->radius*2,this->radius*2);
}

void GBanana::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);

    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->type);
}
