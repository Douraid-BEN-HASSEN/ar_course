#include "widget.h"
#include "ui_widget.h"

#include <QHBoxLayout>
#include "ObstacleGraphics.h"
#include "CheckpointGraphics.h"

#include <Kart/Map/Map.h>
#include <Kart/Game/Properties.h>
#include <Kart/Player/GameMode.h>
#include <Kart/Game/Vehicle.h>

#include <Mqtt/MqttService.h>

Widget::Widget(QWidget *parent): QWidget(parent)
{
    //ui->setupUi(this);
    mScene = new QGraphicsScene(this);
    mScene->setSceneRect(0, 0, 1000,1000);
    mView = new QGraphicsView(this);
    mView->setScene(mScene);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(mView);
    setLayout(layout);
    QGraphicsRectItem* rectItem = new QGraphicsRectItem(0,0,1000,1000);
    rectItem->setBrush(Qt::gray);
    mScene->addItem(rectItem);
    rectItem->setPos(0,0);


    // L'objet que l on observe Field::instance()
    // regarder a chaque fois que cette méthode est appellé
    // Pour finir sur this = Widget apperler updateMap
    connect(Map::getInstance(), SIGNAL(updated()), this, SLOT(updateMap()));
    connect(Properties::getInstance(), SIGNAL(updated()), this, SLOT(updateProperties()));
    connect(GameMode::getInstance(), SIGNAL(updated()), this, SLOT(updateGameMode()));
}

Widget::~Widget() {}

void Widget::updateProperties() {
    ObstacleGraphics::heigth = Properties::getInstance()->getRectangleHeight();
    ObstacleGraphics::width = Properties::getInstance()->getRectangleWidth();
    ObstacleGraphics::radius = Properties::getInstance()->getCircleRadius();

    CheckpointGraphics::radiusCheckpoint = Properties::getInstance()->getCheckpointRadius();

    BananaGraphics::radius = Properties::getInstance()->getBananaRadius();
    BombGraphics::radius = Properties::getInstance()->getBombRadius();
    RocketGraphics::radius = Properties::getInstance()->getRocketRadius();
}

void Widget::updateMap() {

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
    mView->fitInView(mScene->sceneRect(),Qt::KeepAspectRatio);
}

void Widget::updateGameMode() {

    for (Player *iterPlayer : GameMode::getInstance()->_players->values()) {
        PlayerGraphics *playerGraphics = localPlayers.value(iterPlayer->getUuid());

        if (!playerGraphics) {
            playerGraphics = new PlayerGraphics(iterPlayer);
            mScene->addItem(playerGraphics);
            localPlayers.insert(playerGraphics->getUuid(), playerGraphics);
        }
        playerGraphics->updatePlayer(iterPlayer);
    }

    for (ItemGraphics *graphicsItem : localItems) {
        mScene->removeItem(graphicsItem);
    }

    localItems.clear();

    for (Item *item : *GameMode::getInstance()->_items) {
        ItemGraphics *itemGraphics = nullptr;

        if (item->getType() == "banana") {
            itemGraphics = new BananaGraphics(item);
        } else if (item->getType() == "bomb") {
            itemGraphics = new BombGraphics(item);
        } else if (item->getType() == "rocket") {
            itemGraphics = new RocketGraphics(item);
        }

        if (itemGraphics != nullptr) {
            mScene->addItem(itemGraphics);
            localItems.append(itemGraphics);
        }
    }
}

void Widget::resizeEvent(QResizeEvent *event)
{
    mView->fitInView(mScene->sceneRect(),Qt::KeepAspectRatio);
}
