#ifndef GBANANA_H
#define GBANANA_H

#include "GItem.h"

//  +---------------+
//  | Classe Banana |
//  +---------------+
// represente les bananes sur le terain

class GBanana: public GItem
{
public:
    static QString type;
    static float radius;

    GBanana(QPoint, QGraphicsItem *parent = nullptr);
    GBanana(int x, int y, QGraphicsItem *parent = nullptr);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // GBANANA_H
