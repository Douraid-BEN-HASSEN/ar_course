#ifndef GPLAYER_H
#define GPLAYER_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>

#include <Kart/Player/Player.h>

class GPlayer: public QGraphicsObject
{
    Q_OBJECT
public:
    GPlayer(Player *, QGraphicsItem *parent = nullptr);
    QString getUuid();
    qreal getX();
    qreal getY();
    qreal getRadius();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    Player* getPlayer();
private:
    QString uuid;
    qreal x;
    qreal y;
    qreal heigth = 50;
    qreal width = 50;
    Player *_player;
};

#endif // GPLAYER_H
