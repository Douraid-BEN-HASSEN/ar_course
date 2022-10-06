#ifndef GROCKET_H
#define GROCKET_H

#include "GItem.h"

class GRocket: public GItem
{
public:
    static QString type;

    GRocket(QPoint, QGraphicsItem *parent = nullptr);
    GRocket(int x, int y, QGraphicsItem *parent = nullptr);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    const float heigth = 10;
    const float width = 10;
};

#endif // GROCKET_H
