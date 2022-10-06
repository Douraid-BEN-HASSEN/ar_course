#ifndef GROCKET_H
#define GROCKET_H

#include "GItem.h"

class GRocket: public GItem
{
public:
    static QString type;
    static float radius;

    GRocket(QPoint, QGraphicsItem *parent = nullptr);
    GRocket(int x, int y, QGraphicsItem *parent = nullptr);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // GROCKET_H
