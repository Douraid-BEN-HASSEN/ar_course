#ifndef ROCKETGRAPHICS_H
#define ROCKETGRAPHICS_H

#include "ItemGraphics.h"

#include <QPoint>

class RocketGraphics : public ItemGraphics
{
public:
    RocketGraphics(Item *item, QGraphicsItem *parent = nullptr);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    const float heigth = 15;
    const float width = 5;
};

#endif // ROCKETGRAPHICS_H
