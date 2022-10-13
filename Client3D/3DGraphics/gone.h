#ifndef GONE_H
#define GONE_H

#include <QGraphicsObject>
#include <QObject>
#include <Qt3DCore/QEntity>

class GOne: public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    GOne(Qt3DCore::QEntity *mScene, QNode *parent = nullptr);
};

#endif // GONE_H
