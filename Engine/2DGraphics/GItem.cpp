#include "GItem.h"

GItem::GItem(QPoint pos, QGraphicsItem *parent): QGraphicsObject(parent)
{
    this->item = new Item(pos);
    QGraphicsObject::setPos(pos);
}

void GItem::setPos(const QPoint &pos)
{
    this->item->setPos(pos);
    QGraphicsObject::setPos(pos);
}

inline void GItem::setPos(int x, int y)
{
    this->setPos(QPoint(x, y));
}

Item *GItem::getItem()
{
    return item;
}
