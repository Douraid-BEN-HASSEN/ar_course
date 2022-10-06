#ifndef GBOMB_H
#define GBOMB_H

#include "GItem.h"

#include <QPoint>

class GBomb : public GItem
{
public:
    static QString type;
    static float radius;

    GBomb(QPoint, float angle, QGraphicsItem *parent = nullptr);
    GBomb(int x, int y, float angle, QGraphicsItem *parent = nullptr);

    void update() override;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    float _angle = 0;
    int _distanceDrop = 100;
};

#endif // GBOMB_H
