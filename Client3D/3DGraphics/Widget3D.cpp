#include "Widget3D.h"

Qt3DCore::QEntity* Widget3D::createScene()
{
    // Configuration de la scène + spécification de l'entity racine
    //En soi, un Qt3DCore::QEntity est une coquille vide.
    //Le comportement d'un objet Qt3DCore::QEntity est défini par les objets Qt3DCore::QComponent auxquels il fait référence.
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;

    PlaneGraphics3D *planeEntity = new PlaneGraphics3D(rootEntity);

     //planeEntity->mesh()->setHeight(5000.0f);
     //planeEntity->mesh()->setWidth(5000.0f);

     //planeEntity->m_transform->setTranslation(QVector3D(0, 0, 0));
     //planeEntity->mesh()->setMeshResolution(QSize(20, 20));


    return rootEntity;
}

Widget3D::Widget3D(): Qt3DExtras::Qt3DWindow()
{
    mScene = this->createScene();
    // Camera
    camerA = this->camera();
    camerA->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camerA->setPosition(QVector3D(0, 0, 4));
    camerA->setViewCenter(QVector3D(0, 0, 0));
    camerA->setFarPlane(1000);
    //camerA->setFieldOfView(50);

    // For camera controls
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(mScene);
    camController->setLinearSpeed( 50.0f );
    camController->setLookSpeed( 180.0f );
    camController->setCamera(camerA);


    connect(Map::getInstance(), SIGNAL(updated()), this, SLOT(updateMap3D()));
    connect(Properties::getInstance(), SIGNAL(updated()), this, SLOT(updateProperties3D()));
    connect(GameMode::getInstance(), SIGNAL(updated()), this, SLOT(updateGameMode3D()));
    this->setRootEntity(mScene);
}

void Widget3D::updateProperties3D(){
    ObstacleGraphics3D::heigth = Properties::getInstance()->getRectangleHeight();
    ObstacleGraphics3D::width = Properties::getInstance()->getRectangleWidth();
    ObstacleGraphics3D::radius = Properties::getInstance()->getCircleRadius();
    CheckpointGraphics3D::radiusCheckpoint = Properties::getInstance()->getCheckpointRadius();

}

void Widget3D::updateMap3D() {

    QList<Checkpoint*> checkpointList;

    for (Obstacle *iterObstacle : Map::getInstance()->getObstacles()->values()) {
        ObstacleGraphics3D* obstacleGraphics3D = localObstacles3D.value(iterObstacle->getId());
        if(!obstacleGraphics3D){
            obstacleGraphics3D = new ObstacleGraphics3D(iterObstacle, mScene);
            localObstacles3D.insert(obstacleGraphics3D->getId(), obstacleGraphics3D);
        }
        // Modifier la position
        obstacleGraphics3D->updateObstacle3D(iterObstacle);
    }

    for (Checkpoint *iterCheckpoint : Map::getInstance()->getCheckpoints()->values()) {
        CheckpointGraphics3D* checkpointGraphics3D = localCheckpoint3D.value(iterCheckpoint->getId());
        if(!checkpointGraphics3D){
            checkpointGraphics3D = new CheckpointGraphics3D(iterCheckpoint, mScene);
            localCheckpoint3D.insert(checkpointGraphics3D->getId(), checkpointGraphics3D);
        }
        // Modifier la position
        checkpointGraphics3D->updateCheckpoint3D(iterCheckpoint);
        checkpointList.append(iterCheckpoint);
    }

    //tracer des lignes entre les checkpoint
    int nCheckpoint = Map::getInstance()->getCheckpoints()->count();

    for(int it_checkpoint = 0; it_checkpoint < nCheckpoint; it_checkpoint++) {
        if((it_checkpoint+1) >= nCheckpoint) {
            RoadGraphics3D rg3d(checkpointList[it_checkpoint],
                                checkpointList[0],
                                mScene);
        } else {
            RoadGraphics3D rg3d(checkpointList[it_checkpoint],
                                checkpointList[it_checkpoint+1],
                                mScene);
        }

    }

}

void Widget3D::updateGameMode3D() {

    for (Player *iterPlayer : GameMode::getInstance()->_players->values()) {
        PlayerGraphics3D* playerGraphics3D = localPlayers3D.value(iterPlayer->getUuid());
        if(!playerGraphics3D){
            playerGraphics3D = new PlayerGraphics3D(iterPlayer, mScene);
            localPlayers3D.insert(playerGraphics3D->getUuid(), playerGraphics3D);
        }
        // Modifier la position
        playerGraphics3D->updatePlayer3D(iterPlayer);
        playerGraphics3D->followCameraPlayer(iterPlayer, camerA);
    }

}
