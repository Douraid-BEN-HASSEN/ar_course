#include "GPlayer.h"

QString GPlayer::type = "GPlayer";

GPlayer::GPlayer(Player *player, QGraphicsItem *parent): QGraphicsObject{parent}
{
    this->setProperty("type", this->type);

    this->uuid = player->getUuid();
    this->setPos(player->getPosition());
    this->_player = player;
}

QPoint GPlayer::getPos()
{
    return QPoint(this->x(), this->y());
}

Player* GPlayer::getPlayer()
{
    return _player;
}

QString GPlayer::className()
{
    return "className";
}

QString GPlayer::getUuid()
{
    return uuid;
}

QRectF GPlayer::boundingRect() const
{
    return QRectF(-this->heigth/2, -this->width/2,this->heigth,this->width);
}

void GPlayer::setHeigth(int heigth) {
    this->heigth = heigth;
}

void GPlayer::setWidth(int width) {
    this->width = width;
}


void GPlayer::update(Control *control)
{
    if (!control) {
        return;
    }

    this->_angle += -control->getAngle()*0.1;

    float P = 1000;

    // Accélération voulu
    auto F = QPointF(cos(this->_angle), -sin(this->_angle)) *control->getPower();

    // Vitesse actuel = sqrt(vx² * vy²)
    float V = sqrt(_vitesse.x()*_vitesse.x() + _vitesse.y()*_vitesse.y());

    this->_vitesse = (this->_vitesse + F) * 0.1; //0.9 constante pour trainée
    qDebug() << _vitesse;
    qDebug() << this->getPos();

    this->setPos(this->getPos() +this->_vitesse.toPoint());
    this->setRotation(qRadiansToDegrees(-this->_angle));
}

void GPlayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    painter->drawRect(boundingRect());
    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->_player->getPseudo());
}

// void GPlayer::setPos(QPoint a)
// {
//     qDebug("connard");
// }
