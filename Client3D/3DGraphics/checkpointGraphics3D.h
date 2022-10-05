#ifndef CHECKPOINTGRAPH_H
#define CHECKPOINTGRAPH_H

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

class CheckpointGraphics3D: public Qt3DCore::QEntity
{
     Q_OBJECT
public:
    static qreal radiusCheckpoint;
    //CheckpointGraphics3D(QNode *parent = nullptr);
    CheckpointGraphics3D(Checkpoint *, Qt3DCore::QEntity *mScene, QNode *parent = nullptr);
    qreal getId() ;
    qreal getX();
    qreal getY();
    qreal getRadius();

private:
    qreal id;
    qreal x;
    qreal y;

};

#endif // CHECKPOINTGRAPH_H
