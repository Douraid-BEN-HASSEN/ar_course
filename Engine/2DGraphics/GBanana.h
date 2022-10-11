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

    GBanana(QPoint, float angle, QGraphicsItem *parent = nullptr);
    GBanana(int x, int y, float angle, QGraphicsItem *parent = nullptr);

    void update() override;
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // GBANANA_H
