#ifndef PLAYERGRAPHICS_H
#define PLAYERGRAPHICS_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>
#include <QDebug>
#include <QtMath>

#include <Kart/Player/Player.h>

class PlayerGraphics : public QGraphicsObject
{
    Q_OBJECT
public:
    PlayerGraphics(Player *, QGraphicsItem *parent = nullptr);
    void updatePlayer(Player *);

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
signals:

};

#endif // PLAYERGRAPHICS_H
