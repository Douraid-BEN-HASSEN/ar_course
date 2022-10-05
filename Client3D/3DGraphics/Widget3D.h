#ifndef WIDGET3D_H
#define WIDGET3D_H

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

#include "qt3dwindow.h"
#include "3DGraphics/orbittransformcontroller.h"
#include "qorbitcameracontroller.h"

#include <Kart/Map/Map.h>
#include <Kart/Game/Properties.h>
#include <Kart/Player/GameMode.h>

#include <Mqtt/MqttService.h>

#include <QDebug>

#include "obstacleGraphics3D.h"
#include "planeGraphics3D.h"

class Widget3D: public Qt3DExtras::Qt3DWindow
{
    Q_OBJECT

public:
    static Qt3DCore::QEntity *createScene();
    Widget3D();
    Qt3DCore::QEntity* mScene;

private:
    QMap<int, ObstacleGraphics3D*> localObstacles3D;
    //QMap<int, CheckpointGraphics*> localCheckpoint;
    //QMap<QString, PlayerGraphics*> localPlayers;


private slots:
    void updateMap3D();
};

#endif // WIDGET3D_H
