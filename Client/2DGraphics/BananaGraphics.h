#ifndef BANANAGRAPHICS_H
#define BANANAGRAPHICS_H

#include "ItemGraphics.h"

#include <QPoint>

class BananaGraphics : public ItemGraphics
{
public:
    BananaGraphics(Item *item, QGraphicsItem *parent = nullptr);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    const float heigth = 10;
    const float width = 10;
};

#endif // BANANAGRAPHICS_H
