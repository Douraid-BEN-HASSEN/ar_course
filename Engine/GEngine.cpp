#include "GEngine.h"

GEngine::GEngine(QWidget *parent): QWidget(parent)
{
    this->mScene = new QGraphicsScene(this);
    this->mScene->setSceneRect(0, 0, 1000,1000);
    this->mView = new QGraphicsView(this);
    this->mView->setScene(mScene);
}

GEngine::~GEngine()
{

}

void GEngine::addCheckpoint(Checkpoint *pCheckpoint)
{
    GCheckpoint *g_checkpoint = new GCheckpoint(pCheckpoint);
    //CheckpointGraphics *checkpointGraphics = new CheckpointGraphics(pCheckpoint);

    this->localCheckpoint.insert(pCheckpoint->getId(), g_checkpoint);
}

void GEngine::addObstacle(Obstacle *pObstacle)
{
    GObstacle *g_obstacle = new GObstacle(pObstacle);
    this->localObstacles.insert(pObstacle->getId(), g_obstacle);
}

void GEngine::updateGraphics()
{
    /*this->mScene = new QGraphicsScene(this);
    this->mScene->setSceneRect(0, 0, 1000,1000);
    this->mView = new QGraphicsView(this);
    this->mView->setScene(mScene);*/

    for(int iCheckpoint=0; iCheckpoint<this->localCheckpoint.count(); iCheckpoint++) {
        mScene->addItem(this->localCheckpoint[iCheckpoint]);
    }

    for(int iObstacle=0; iObstacle<this->localObstacles.count(); iObstacle++) {
        mScene->addItem(this->localObstacles[iObstacle]);
    }


}
