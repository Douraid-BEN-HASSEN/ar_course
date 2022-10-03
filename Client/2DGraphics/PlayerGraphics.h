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
    void updatePlayer(Player *);
    PlayerGraphics(Player *, QGraphicsItem *parent = nullptr);
    QString getUuid();
    qreal getX();
    qreal getY();
    qreal getHeigth();
    qreal getWidth();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    Player* getPlayer();
    static qreal heigth;
    static qreal width;

private:
    QString uuid;
    qreal x;
    qreal y;
    Player *_player;
signals:

};

#endif // PLAYERGRAPHICS_H
