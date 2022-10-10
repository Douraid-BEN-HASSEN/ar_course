#include "ItemGraphics.h"

ItemGraphics::ItemGraphics(Item *item, QGraphicsItem *parent): QGraphicsObject(parent)
{

}

QPoint ItemGraphics::getPos()
{
    return QPoint(this->x(), this->y());
}
