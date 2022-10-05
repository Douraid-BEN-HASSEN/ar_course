#ifndef GBOMB_H
#define GBOMB_H

#include "GItem.h"

#include <QPoint>

class GBomb : public GItem
{
public:
    GBomb(Item *item, QGraphicsItem *parent = nullptr);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    const float heigth = 10;
    const float width = 10;
};

#endif // GBOMB_H
