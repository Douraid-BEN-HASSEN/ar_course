#ifndef PLAYERGRAPHICS_H
#define PLAYERGRAPHICS_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>
#include <QDebug>
#include <QtMath>

#include "Qt3DExtras/Qt3DWindow"
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DRender/QMesh>
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

#include <Kart/Player/Player.h>
#include <Kart/Game/Vehicle.h>
#include <Kart/Game/Properties.h>

class PlayerGraphics3D : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    void updatePlayer3D(Player *);
    void followCameraPlayer(Player *, Qt3DRender::QCamera *camerA);
    PlayerGraphics3D(Player *, Qt3DCore::QEntity* mScene,  QNode *parent = nullptr);
    QString getUuid();
    qreal getX();
    qreal getY();
    qreal getRadius();
    qreal getHeigth();
    qreal getWidth();
    Player* getPlayer();
    static qreal heigth;
    static qreal width;


private:
    QString uuid;
    qreal x;
    qreal y;
    Player *_player;
signals:

};

#endif // PLAYERGRAPHICS_H
