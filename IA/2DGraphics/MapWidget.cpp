#include "MapWidget.h"

#include <QHBoxLayout>
#include "ObstacleGraphics.h"
#include "CheckpointGraphics.h"

#include <Kart/Map/Map.h>
#include <Kart/Game/Properties.h>
#include <Kart/Player/GameMode.h>

#include <Mqtt/MqttService.h>

MapWidget::MapWidget(QWidget *parent)
    : QWidget{parent}
{
    mScene = new QGraphicsScene(this);
    mScene->setSceneRect(0, 0, 1000,1000);
    mView = new QGraphicsView(this);
    mView->setScene(mScene);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(mView);
    setLayout(layout);

    // L'objet que l on observe Field::instance()
    // regarder a chaque fois que cette méthode est appellé
    // Pour finir sur this = Widget apperler updateMap
    connect(Map::getInstance(), SIGNAL(updated()), this, SLOT(updateMap()));
    connect(Properties::getInstance(), SIGNAL(updated()), this, SLOT(updateProperties()));
    connect(GameMode::getInstance(), SIGNAL(updated()), this, SLOT(updateGameMode()));

}

MapWidget::~MapWidget()
{
}

void MapWidget::updateProperties() {
    ObstacleGraphics::heigth = Properties::getInstance()->getRectangleHeight();
    ObstacleGraphics::width = Properties::getInstance()->getRectangleWidth();
    ObstacleGraphics::radius = Properties::getInstance()->getCircleRadius();

    CheckpointGraphics::radiusCheckpoint = Properties::getInstance()->getCheckpointRadius();
}

void MapWidget::updateMap() {

    //new QMap<int, Obstacle*>();
    // Faire une boucle sur tous les obstacles
    // Sur chaque obstacle on va devoir le créer + le placer

    for (Obstacle *iterObstacle : Map::getInstance()->getObstacles()->values()) {
        // Verifier si l object ObstacleRect* obstaclerect  exist

        ObstacleGraphics *obstacleGraphics = localObstacles.value(iterObstacle->getId());

        if (!obstacleGraphics) {
            obstacleGraphics = new ObstacleGraphics(iterObstacle);
            mScene->addItem(obstacleGraphics);
            localObstacles.insert(obstacleGraphics->getId(), obstacleGraphics);
        }

        obstacleGraphics->setPos(iterObstacle->getX(),iterObstacle->getY());
    }


    for (Checkpoint *iterCheckpoint : Map::getInstance()->getCheckpoints()->values()) {

        CheckpointGraphics *checkpointGraphics = localCheckpoint.value(iterCheckpoint->getId());

        if (!checkpointGraphics) {
            checkpointGraphics = new CheckpointGraphics(iterCheckpoint);

            mScene->addItem(checkpointGraphics);
            localCheckpoint.insert(checkpointGraphics->getId(), checkpointGraphics);
        }

        checkpointGraphics->setPos(iterCheckpoint->getX(), iterCheckpoint->getY());
    }

}

void MapWidget::updateGameMode() {

    for (Player *iterPlayer : GameMode::getInstance()->_players->values()) {

        PlayerGraphics *playerGraphics = localPlayers.value(iterPlayer->getUuid());

        if (!playerGraphics) {
            playerGraphics = new PlayerGraphics(iterPlayer);
            mScene->addItem(playerGraphics);
            localPlayers.insert(playerGraphics->getUuid(), playerGraphics);
        }

/*        qDebug() << QString("Angle : %1, X : %2, Y : %3").arg(
                        QString::number(iterPlayer->getAngle()),
                        QString::number(iterPlayer->getX()),
                        QString::number(iterPlayer->getY())
                        );*/

        playerGraphics->updatePlayer(iterPlayer);
//        playerGraphics->setPos(iterPlayer->getX(), iterPlayer->getY());
    }

}

void MapWidget::drawPath(QList<QPair<QString, Checkpoint *>> path)
{
    qDebug() << "ICIIIIIIIIIIIIIIIIIIIIIIIIIIIII";
    // draw path
    int pairs = path.count();
    for(int nPair=0; nPair < path.count(); nPair++) {

        if((nPair+1) < pairs) {
            QLineF ligne(QPoint(path[nPair].second->getX(), path[nPair].second->getY()),
                    QPoint(path[nPair+1].second->getX(), path[nPair+1].second->getY()));


            this->mScene->addLine(ligne, QPen( Qt::black, 10 ));
        } else {
            QLineF ligne(QPoint(path[nPair].second->getX(), path[nPair].second->getY()),
                    QPoint(path[0].second->getX(), path[0].second->getY()));
            this->mScene->addLine(ligne, QPen( Qt::black, 10 ));
        }

    }
}

void MapWidget::resizeEvent(QResizeEvent *event)
{
    mView->fitInView(mScene->sceneRect(),Qt::KeepAspectRatio);
}
