#include "GEngine.h"
// Maps : avoir les angles, update toutes les 1s
// Egine : limite map
GEngine::GEngine(QWidget *parent): QWidget(parent)
{
    this->mScene = new QGraphicsScene(this);
    this->mScene->setSceneRect(0, 0, 1000,1000);
    this->mView = new QGraphicsView(this);
    this->mView->setScene(mScene);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(mView);
    setLayout(layout);

    this->mView->fitInView(mScene->sceneRect(),Qt::KeepAspectRatio);
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

void GEngine::addPlayer(Player* pPlayer)
{
    GPlayer *g_player = new GPlayer(pPlayer);
    this->mScene->addItem(g_player);
    this->localPlayers.insert(g_player->getUuid(), g_player);
    g_player->setPos(pPlayer->getX(),pPlayer->getY());
}

void GEngine::updateCheckpoint(Checkpoint *pCheckpoint)
{
    GCheckpoint *g_checkpoint = this->localCheckpoint.value(pCheckpoint->getId());

    if(g_checkpoint) {
        this->mScene->removeItem(g_checkpoint);
        this->localObstacles.remove(pCheckpoint->getId());
    }

    g_checkpoint = new GCheckpoint(pCheckpoint);
    this->mScene->addItem(g_checkpoint);
    this->localCheckpoint.insert(g_checkpoint->getId(), g_checkpoint);
    g_checkpoint->setPos(pCheckpoint->getX(),pCheckpoint->getY());
}

void GEngine::updateObstacle(Obstacle *pObstacle)
{
    GObstacle *g_obstacle = this->localObstacles.value(pObstacle->getId());

    if(g_obstacle) {
        this->mScene->removeItem(g_obstacle);
        this->localObstacles.remove(pObstacle->getId());
    }

    g_obstacle = new GObstacle(pObstacle);
    this->mScene->addItem(g_obstacle);
    this->localObstacles.insert(g_obstacle->getId(), g_obstacle);
    g_obstacle->setPos(pObstacle->getX(),pObstacle->getY());
}

void GEngine::updatePlayer(Player *pPlayer)
{
    GPlayer *g_player = this->localPlayers.value(pPlayer->getUuid());

    if(g_player) {
        this->mScene->removeItem(g_player);
        this->localPlayers.remove(pPlayer->getUuid());
    }

    g_player = new GPlayer(pPlayer);
    this->mScene->addItem(g_player);
    this->localPlayers.insert(g_player->getUuid(), g_player);
    g_player->setPos(pPlayer->getX(),pPlayer->getY());

}

QList<QGraphicsItem *> GEngine::collision(Player* pPlayer)
{
    QList<QGraphicsItem*> g_items;
    QGraphicsItem* g_player = this->localPlayers.value(pPlayer->getUuid());

    for(GCheckpoint *g_checkpoint: this->localCheckpoint) {
        if(g_checkpoint->collidesWithItem(g_player)) g_items.append(g_checkpoint);
    }

    for(GObstacle *g_obstacle: this->localObstacles) {
        if(g_obstacle->collidesWithItem(g_player)) g_items.append(g_obstacle);
    }

    for(GPlayer *g_player: this->localPlayers) {
        if(g_player->getUuid() != pPlayer->getUuid() && g_player->collidesWithItem(g_player)) g_items.append(g_player);
    }

    return g_items;
}

void GEngine::resizeEvent(QResizeEvent *event)
{
    mView->fitInView(mScene->sceneRect(),Qt::KeepAspectRatio);
}
