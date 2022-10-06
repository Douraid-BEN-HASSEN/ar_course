#ifndef GBOMB_H
#define GBOMB_H

#include "GItem.h"

#include <QPoint>

class GBomb : public GItem
{
public:
    static QString type;
    static float radius;

    GBomb(QPoint, QGraphicsItem *parent = nullptr);
    GBomb(int x, int y, QGraphicsItem *parent = nullptr);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // GBOMB_H
