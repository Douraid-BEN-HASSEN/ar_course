#include "GItem.h"

GItem::GItem(Item *item, QGraphicsItem *parent): QGraphicsObject(parent)
{

}

QPoint GItem::getPos()
{
    return QPoint(this->x(), this->y());
}
