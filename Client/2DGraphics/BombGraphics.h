#ifndef BOMBGRAPHICS_H
#define BOMBGRAPHICS_H

#include "ItemGraphics.h"

#include <QPoint>

class BombGraphics : public ItemGraphics
{
public:
    BombGraphics(Item *item, QGraphicsItem *parent = nullptr);

    static qreal radius;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // BOMBGRAPHICS_H
