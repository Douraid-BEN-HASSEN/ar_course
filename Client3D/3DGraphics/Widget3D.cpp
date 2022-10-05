#include "Widget3D.h"

Qt3DCore::QEntity* Widget3D::createScene()
{
    // Configuration de la scène + spécification de l'entity racine
    //En soi, un Qt3DCore::QEntity est une coquille vide.
    //Le comportement d'un objet Qt3DCore::QEntity est défini par les objets Qt3DCore::QComponent auxquels il fait référence.
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;

    PlaneGraphics3D *planeEntity = new PlaneGraphics3D(rootEntity);

     planeEntity->mesh()->setHeight(10.0f);
     planeEntity->mesh()->setWidth(10.0f);
     planeEntity->mesh()->setMeshResolution(QSize(20, 20));


    return rootEntity;
}

Widget3D::Widget3D(): Qt3DExtras::Qt3DWindow()
{
    mScene = this->createScene();
    // Camera
    Qt3DRender::QCamera *camera = this->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // For camera controls
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(mScene);
    camController->setLinearSpeed( 50.0f );
    camController->setLookSpeed( 180.0f );
    camController->setCamera(camera);


    connect(Map::getInstance(), SIGNAL(updated()), this, SLOT(updateMap3D()));
    //connect(Properties::getInstance(), SIGNAL(updated()), this, SLOT(updateProperties()));
    //connect(GameMode::getInstance(), SIGNAL(updated()), this, SLOT(updateGameMode()));
    this->setRootEntity(mScene);
}

void Widget3D::updateMap3D() {
    for (Obstacle *iterObstacle : Map::getInstance()->getObstacles()->values()) {
        qDebug() << "appel updateMap3D";
        ObstacleGraphics3D* obstacleGraphics3D = new ObstacleGraphics3D(iterObstacle, mScene);
    }


}
