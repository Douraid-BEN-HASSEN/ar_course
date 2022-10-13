#ifndef BANANAGRAPHICS_H
#define BANANAGRAPHICS_H

#include "ItemGraphics.h"

#include <QPoint>

class BananaGraphics : public ItemGraphics
{
public:
    BananaGraphics(Item *item, QGraphicsItem *parent = nullptr);

    static qreal radius;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // BANANAGRAPHICS_H
