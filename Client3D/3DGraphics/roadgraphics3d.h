#ifndef ROADGRAPHICS3D_H
#define ROADGRAPHICS3D_H

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
#include <Qt3DExtras/QPlaneMesh>
#include <QPropertyAnimation>

#include <QDiffuseSpecularMaterial>
#include <QOrbitCameraController>

#include <Kart/Map/Checkpoint.h>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QAttribute>
#include <cmath>
#include <QVector2D>


#include "planeGraphics3D.h"

class RoadGraphics3D: public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    RoadGraphics3D(Checkpoint *, Checkpoint *, Qt3DCore::QEntity *mScene, QNode *parent = nullptr);
    virtual ~RoadGraphics3D() {};

    void drawLine(const QVector3D& start, const QVector3D& end, const QColor& color, Qt3DCore::QEntity *mScene, float ref =0);
    void drawLine3D(Checkpoint *checkpoint1, Checkpoint *checkpoint2, Qt3DCore::QEntity *mScene);

};

#endif // ROADGRAPHICS3D_H
