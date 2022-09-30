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
    this->mScene->addItem(g_checkpoint);
    this->localCheckpoint.insert(g_checkpoint->getId(), g_checkpoint);
    g_checkpoint->setPos(pCheckpoint->getX(),pCheckpoint->getY());
}

void GEngine::addObstacle(Obstacle *pObstacle)
{
    GObstacle *g_obstacle = new GObstacle(pObstacle);
    this->mScene->addItem(g_obstacle);
    this->localObstacles.insert(g_obstacle->getId(), g_obstacle);
    g_obstacle->setPos(pObstacle->getX(),pObstacle->getY());
}

void GEngine::updateCheckpoint(Checkpoint *pCheckpoint)
{
    GCheckpoint *g_checkpoint = this->localCheckpoint.value(pCheckpoint->getId());

    this->mScene->removeItem(g_checkpoint);
    this->localObstacles.remove(pCheckpoint->getId());

    g_checkpoint = new GCheckpoint(pCheckpoint);
    this->mScene->addItem(g_checkpoint);
    this->localCheckpoint.insert(g_checkpoint->getId(), g_checkpoint);
    g_checkpoint->setPos(pCheckpoint->getX(),pCheckpoint->getY());
}

void GEngine::updateObstacle(Obstacle *pObstacle)
{
    GObstacle *g_obstacle = this->localObstacles.value(pObstacle->getId());

    this->mScene->removeItem(g_obstacle);
    this->localObstacles.remove(pObstacle->getId());

    g_obstacle = new GObstacle(pObstacle);
    this->mScene->addItem(g_obstacle);
    this->localObstacles.insert(g_obstacle->getId(), g_obstacle);
    g_obstacle->setPos(pObstacle->getX(),pObstacle->getY());
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
