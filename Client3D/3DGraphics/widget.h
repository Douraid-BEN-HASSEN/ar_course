#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QtMqtt/QtMqtt>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "obstacleGraphics3D.h"
#include "playerGraphics3D.h"

#include "checkpointGraphics3D.h"

#include "qt3dwindow.h"
//#include "3DGraphics/orbittransformcontroller.h"
// #include "qorbitcameracontroller.h"
#include <QApplication>
//#include "interface.h"


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

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QMap<int, ObstacleGraphics*> localObstacles;
    QMap<int, CheckpointGraphics*> localCheckpoint;
    QMap<QString, PlayerGraphics*> localPlayers;

    QGraphicsScene* mScene;
    QGraphicsView* mView;
    Qt3DExtras::Qt3DWindow *mView3D;

private slots:
    void updateMap();
    void updateProperties();
    void updateGameMode();

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};
#endif // WIDGET_H
