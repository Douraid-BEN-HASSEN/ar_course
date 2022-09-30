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
    QString getUuid() ;
    qreal getX();
    qreal getY();
    qreal getRadius();
    qreal getAngle();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QString uuid;
    qreal x;
    qreal y;
    qreal heigth = 50;
    qreal width = 50;
    qreal angle = 0;
signals:

};

#endif // PLAYERGRAPHICS_H
