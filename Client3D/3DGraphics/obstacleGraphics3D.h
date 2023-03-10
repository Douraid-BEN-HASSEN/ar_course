#ifndef OBSTACLEGRAPH_H
#define OBSTACLEGRAPH_H

#include <QtMath>

#include "Qt3DExtras/Qt3DWindow"
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <QPropertyAnimation>

#include <QDiffuseSpecularMaterial>
#include <QOrbitCameraController>

#include <Kart/Map/Obstacle.h>

class ObstacleGraphics3D : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    ObstacleGraphics3D(Obstacle *, Qt3DCore::QEntity *mScene, QNode *parent = nullptr);
    void updateObstacle3D(Obstacle *);
    static qreal heigth;
    static qreal width;
    static qreal radius;

    qreal getId() ;
    qreal getX();
    qreal getY();
    qreal getHeigth();
    qreal getWidth();
    qreal getRadius();
    qreal getAngle();

private:
    qreal id;
    qreal x;
    qreal y;
    qreal angle;
    // Récupérer depuis /game/properties
};

#endif // OBSTACLEGRAPH_H
