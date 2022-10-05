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
    return QRectF(-50, -50,100.,100.);
}

void GPlayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    painter->drawRect(boundingRect());
    this->setRotation(this->_player->getAngle());

    painter->setPen(Qt::black);
    painter->drawText(0, 0, this->_player->getPseudo());
}

void GPlayer::update(Control *control)
{
    if (!control) {
        return;
    }

    this->_angle += control->getAngle()*0.1;

    float P = 1000;

    // Accélération voulu
    auto F = QPointF(cos(this->_angle), -sin(this->_angle)) *control->getPower();

    // Vitesse actuel = sqrt(vx² * vy²)
    float V = sqrt(_vitesse.x()*_vitesse.x() + _vitesse.y()*_vitesse.y());

    this->_vitesse = (this->_vitesse + F) * 0.1; //0.9 constante pour trainée
    qDebug() << _vitesse;
    qDebug() << this->getPos();

    this->setPos(this->getPos() +this->_vitesse.toPoint());
}

// void GPlayer::setPos(QPoint a)
// {
//     qDebug("connard");
// }