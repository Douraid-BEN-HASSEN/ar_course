#ifndef GBANANA_H
#define GBANANA_H


#include <QGraphicsObject>
#include <QObject>
#include <QPainter>
#include <QBrush>

#include <Kart/Player/Item.h>
//  +---------------+
//  | Classe Banana |
//  +---------------+
// represente les bananes sur le terain

class GBanana: public QGraphicsObject
{
     Q_OBJECT
public:
    static QString type;

    GBanana();
    GBanana(Item *, QGraphicsItem *parent = nullptr);
    Item *getItem();

    qreal getX();
    qreal getY();
    qreal getRadius();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    Item *banana;
    qreal x;
    qreal y;
    qreal radiusBanana;
};


#endif // GBANANA_H
