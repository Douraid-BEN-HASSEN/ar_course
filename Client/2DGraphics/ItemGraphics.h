#ifndef ITEMGRAPHICS_H
#define ITEMGRAPHICS_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>

#include <Kart/Player/Item.h>

class ItemGraphics: public QGraphicsObject
{
    Q_OBJECT
public:
    ItemGraphics(Item *item, QGraphicsItem *parent = nullptr);

    QPoint getPos();

    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

protected:
    QString type = "__item__";

    const float heigth = 5;
    const float width = 5;

};

#endif // ITEMGRAPHICS_H
