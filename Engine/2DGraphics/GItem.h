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
    GItem(QPoint pos, QString type, QGraphicsItem *parent = nullptr);

    void setPos(const QPoint &pos);
    inline void setPos(int x, int y);

    Item *getItem();
    void setTtl(int);
    int getTtl();

    virtual void update() = 0;
    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

protected:
    QString type = "__item__";

    const float heigth = 5;
    const float width = 5;

    Item *item;

private:
    int ttl = -1;
};

#endif // GITEM_H
