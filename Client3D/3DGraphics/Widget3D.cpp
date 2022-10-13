#include "Widget3D.h"

static int iterKey = 0;

Qt3DCore::QEntity* Widget3D::createScene()
{
    // Configuration de la scène + spécification de l'entity racine
    //En soi, un Qt3DCore::QEntity est une coquille vide.
    //Le comportement d'un objet Qt3DCore::QEntity est défini par les objets Qt3DCore::QComponent auxquels il fait référence.
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;

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
    camController->setLinearSpeed( 500.0f );
    camController->setLookSpeed( 180.0f );
    camController->setCamera(camerA);


    connect(Map::getInstance(), SIGNAL(updated()), this, SLOT(updateMap3D()));
    connect(Properties::getInstance(), SIGNAL(updated()), this, SLOT(updateProperties3D()));
    connect(GameMode::getInstance(), SIGNAL(updated()), this, SLOT(updateGameMode3D()));
    this->setRootEntity(mScene);
}


void Widget3D::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_P) {
      if(iterKey + 1 < GameMode::getInstance()->_players->size()){
      iterKey ++;
      }
    }
    if (e->key() == Qt::Key_O) {
      if(iterKey - 1 >= 0){
      iterKey -- ;
      }
    }
}



void Widget3D::updateProperties3D(){
    ObstacleGraphics3D::heigth = Properties::getInstance()->getRectangleHeight();
    ObstacleGraphics3D::width = Properties::getInstance()->getRectangleWidth();
    ObstacleGraphics3D::radius = Properties::getInstance()->getCircleRadius();
    CheckpointGraphics3D::radiusCheckpoint = Properties::getInstance()->getCheckpointRadius();
    BananaGraphics3D::bananaRadius = Properties::getInstance()->getBananaRadius();
    RocketGraphics3D::rocketRadius = Properties::getInstance()->getRocketRadius();
    BombGraphics3D::bombRadius = Properties::getInstance()->getBombRadius();
}

void Widget3D::updateMap3D() {

    QList<Checkpoint*> checkpointList;
    QList<int> checkpointIds;

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
        checkpointGraphics3D->updateCheckpoint3D(iterCheckpoint, playerCamFocus);
        checkpointList.append(iterCheckpoint);
        checkpointIds.append(iterCheckpoint->getId());
    }

    // trier les checkpoints
    std::sort(checkpointIds.begin(), checkpointIds.end()); // sort id
    QList<Checkpoint*> checkpointListSorted;
    int iId = 0;

    while((iId+1) < checkpointList.count()) {
        for (Checkpoint *iterCheckpoint : Map::getInstance()->getCheckpoints()->values()) {
            if(checkpointIds[iId] == iterCheckpoint->getId()){
                checkpointListSorted.append(iterCheckpoint);
                iId++;
            }
        }
    }

    //tracer des lignes entre les checkpoint
    int nCheckpoint = Map::getInstance()->getCheckpoints()->count();

    for(int it_checkpoint = 0; it_checkpoint < nCheckpoint; it_checkpoint++) {
        if((it_checkpoint+1) >= nCheckpoint) {
            RoadGraphics3D rg3d(checkpointListSorted[it_checkpoint],
                                checkpointListSorted[0],
                                mScene);
          //qDebug() << "je suis passé par  = " << checkpointListSorted[it_checkpoint] ;

        } else {
            RoadGraphics3D rg3d(checkpointListSorted[it_checkpoint],
                                checkpointListSorted[it_checkpoint+1],
                                mScene);


        }
    }
}

void Widget3D::updateGameMode3D() {

    int iter = 0;
    for (Player *iterPlayer : GameMode::getInstance()->_players->values()) {
        PlayerGraphics3D* playerGraphics3D = localPlayers3D.value(iterPlayer->getUuid());
        if(!playerGraphics3D){
            playerGraphics3D = new PlayerGraphics3D(iterPlayer, mScene);
            localPlayers3D.insert(playerGraphics3D->getUuid(), playerGraphics3D);
        }
        // Modifier la position
        playerGraphics3D->updatePlayer3D(iterPlayer);
        if(iter == iterKey){
            playerCamFocus = iterPlayer;
            playerGraphics3D->followCameraPlayer(playerCamFocus, camerA);
        }
        iter++;
    }

    for (Item *iterItem : GameMode::getInstance()->_items->values()){
        BananaGraphics3D* bananaGraphics3D = localBanana3D.value(iterItem->getUuid());
        RocketGraphics3D* rocketGraphics3D = localRocket3D.value(iterItem->getUuid());
        BombGraphics3D* bombGraphics3D = localBomb3D.value(iterItem->getUuid());

        if(iterItem->getType() == "banana"){
            if(!bananaGraphics3D){
                bananaGraphics3D = new BananaGraphics3D(iterItem, mScene);
                localBanana3D.insert(bananaGraphics3D->getUuid(), bananaGraphics3D);
            }
            bananaGraphics3D->updateBanana3D(iterItem);
        }

        if(iterItem->getType() == "rocket"){
            if(!rocketGraphics3D){
                rocketGraphics3D = new RocketGraphics3D(iterItem, mScene);
                localRocket3D.insert(rocketGraphics3D->getUuid(), rocketGraphics3D);
            }
            rocketGraphics3D->updateRocket3D(iterItem);
        }

        if(iterItem->getType() == "bomb"){
            if(!bombGraphics3D){
                bombGraphics3D = new BombGraphics3D(iterItem, mScene);
                localBomb3D.insert(bombGraphics3D->getUuid(), bombGraphics3D);
            }
            bombGraphics3D->updateBomb3D(iterItem);
        }
    }

   for(BananaGraphics3D *bananaLocal : localBanana3D.values()){
        Item *itemCondition = GameMode::getInstance()->_items->value(bananaLocal->getUuid());
        if(!itemCondition){
            bananaLocal->setEnabled(false);
            localBanana3D.remove(bananaLocal->getUuid());
        }
   }

   for(RocketGraphics3D *rocketLocal : localRocket3D.values()){
        Item *itemCondition = GameMode::getInstance()->_items->value(rocketLocal->getUuid());
        if(!itemCondition){
            rocketLocal->setEnabled(false);
            localRocket3D.remove(rocketLocal->getUuid());
        }
   }

   for(BombGraphics3D *bombLocal : localBomb3D.values()){
        Item *itemCondition = GameMode::getInstance()->_items->value(bombLocal->getUuid());
        if(!itemCondition || bombLocal->getX() > 1000 ||  bombLocal->getY() > 1000 || bombLocal->getX() < -1000 || bombLocal->getY() < -1000){
            bombLocal->setEnabled(false);
            localBomb3D.remove(bombLocal->getUuid());
        }
   }

}








