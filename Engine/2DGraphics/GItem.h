#ifndef GITEM_H
#define GITEM_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>

#include <Kart/Player/Item.h>

class GItem: public QGraphicsObject
{
    Q_OBJECT
public:
    GItem(Item *item, QGraphicsItem *parent = nullptr);

    QPoint getPos();

    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

protected:
    QString type = "__item__";

    const float heigth = 5;
    const float width = 5;
};

#endif // GITEM_H
