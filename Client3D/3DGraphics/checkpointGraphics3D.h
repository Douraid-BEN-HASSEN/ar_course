#ifndef CHECKPOINTGRAPH_H
#define CHECKPOINTGRAPH_H

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
#include <Qt3DExtras/QText2DEntity>
#include <QPropertyAnimation>
#include <Qt3DExtras/QText2DEntity>
#include <QDiffuseSpecularMaterial>
#include <QOrbitCameraController>
#include <Kart/Map/Checkpoint.h>
#include <Kart/Player/GameMode.h>

class CheckpointGraphics3D: public Qt3DCore::QEntity
{
     Q_OBJECT
public:
    static qreal radiusCheckpoint;
    CheckpointGraphics3D(Checkpoint *, Qt3DCore::QEntity *mScene, int mapIndex, QNode *parent = nullptr);
    void updateCheckpoint3D(Checkpoint *, Player *);
    qreal getId() ;
    qreal getX();
    qreal getY();
    qreal getRadius();

private:
    qreal id;
    qreal x;
    qreal y;

    Qt3DExtras::QText2DEntity *text2D;
    Qt3DCore::QTransform *textTransform;

};

#endif // CHECKPOINTGRAPH_H
