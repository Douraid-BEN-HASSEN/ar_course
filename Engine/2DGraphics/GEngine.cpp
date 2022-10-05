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

    this->mView->fitInView(mScene->sceneRect(), Qt::KeepAspectRatio);
}

GEngine::~GEngine() {}

void GEngine::addCheckpointGraphics(GCheckpoint *gCheckpoint)
{
    this->mScene->addItem(gCheckpoint);
}

void GEngine::addObstacleGraphics(GObstacle *gObstacle)
{
    this->mScene->addItem(gObstacle);
}

void GEngine::addPlayerGraphics(GPlayer* gPlayer)
{
    this->mScene->addItem(gPlayer);
}

void GEngine::resizeEvent(QResizeEvent *event)
{
    mView->fitInView(mScene->sceneRect(),Qt::KeepAspectRatio);
}
