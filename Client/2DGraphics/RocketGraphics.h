#ifndef ROCKETGRAPHICS_H
#define ROCKETGRAPHICS_H

#include "ItemGraphics.h"

#include <QPoint>

class RocketGraphics : public ItemGraphics
{
public:
    RocketGraphics(Item *item, QGraphicsItem *parent = nullptr);

    static qreal radius;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // ROCKETGRAPHICS_H
