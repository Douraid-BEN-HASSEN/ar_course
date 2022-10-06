#ifndef GROCKET_H
#define GROCKET_H

#include "GItem.h"
#include <QVector2D>

class GRocket: public GItem
{
public:
    static QString type;
    static float radius;

    GRocket(QPoint, float angle, QGraphicsItem *parent = nullptr);
    GRocket(int x, int y, float angle, QGraphicsItem *parent = nullptr);

    void update() override;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    float _angle = 0;
};

#endif // GROCKET_H
