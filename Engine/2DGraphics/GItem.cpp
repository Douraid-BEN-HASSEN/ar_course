#include "GItem.h"

GItem::GItem(QPoint pos, float angle, QString type, QGraphicsItem *parent): QGraphicsObject(parent)
{
    this->item = new Item(pos, angle, type);
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

void GItem::setTtl(int ttl) {
    this->ttl = ttl;
}

int GItem::getTtl() {
    return this->ttl;
}

QPainterPath GItem::shape() const
{
    QPainterPath path;
    if (this->boundingRect().isNull())
        return path;

    path.addEllipse(this->boundingRect());

    return path;
}
