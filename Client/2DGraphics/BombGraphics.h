#ifndef BOMBGRAPHICS_H
#define BOMBGRAPHICS_H

#include "ItemGraphics.h"

#include <QPoint>

class BombGraphics : public ItemGraphics
{
public:
    BombGraphics(Item *item, QGraphicsItem *parent = nullptr);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    const float heigth = 10;
    const float width = 10;
};

#endif // BOMBGRAPHICS_H
