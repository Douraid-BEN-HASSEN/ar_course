#ifndef ROADGRAPHICS3D_H
#define ROADGRAPHICS3D_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>
#include <QBrush>

#include "Qt3DExtras/Qt3DWindow"
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <QPropertyAnimation>

#include <QDiffuseSpecularMaterial>
#include <QOrbitCameraController>

#include <Kart/Map/Checkpoint.h>

class RoadGraphics3D: public Qt3DCore::QEntity
{
public:
    RoadGraphics3D();
    RoadGraphics3D(Checkpoint *, Checkpoint *, Qt3DCore::QEntity *mScene, QNode *parent = nullptr);
private:
    qreal id;
    qreal x;
    qreal y;
};

#endif // ROADGRAPHICS3D_H
