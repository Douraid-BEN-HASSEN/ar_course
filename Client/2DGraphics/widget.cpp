#include "widget.h"
#include "ui_widget.h"

#include <QHBoxLayout>
#include "ObstacleGraphics.h"
#include "CheckpointGraphics.h"

#include <Kart/Map/Map.h>
#include <Kart/Game/Properties.h>
#include <Kart/Player/GameMode.h>

#include <Mqtt/MqttService.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mScene = new QGraphicsScene(this);
    mScene->setSceneRect(0, 0, 1000,1000);
    mView = new QGraphicsView(this);
    mView->setScene(mScene);

    // L'objet que l on observe Field::instance()
    // regarder a chaque fois que cette méthode est appellé
    // Pour finir sur this = Widget apperler updateMap
    connect(Map::getInstance(), SIGNAL(updated()), this, SLOT(updateMap()));
    connect(Properties::getInstance(), SIGNAL(updated()), this, SLOT(updateProperties()));
<<<<<<< HEAD

=======
    connect(GameMode::getInstance(), SIGNAL(updated()), this, SLOT(updateGameMode()));
>>>>>>> dev
}

Widget::~Widget()
{
    delete ui;
}

<<<<<<< HEAD
void Widget::updateProperties(){
    ObstacleGraphics::heigth = Properties::getInstance()->getRectangleHeight();
    ObstacleGraphics::width = Properties::getInstance()->getRectangleWidth();
    ObstacleGraphics::radius = Properties::getInstance()->getCircleRadius();

}

void Widget::updateMap(){
=======
void Widget::updateMap() {

    qDebug() << "map";
>>>>>>> dev
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
            checkpointGraphics->setPos(iterCheckpoint->getX(), iterCheckpoint->getY());

            mScene->addItem(checkpointGraphics);
            localCheckpoint.insert(checkpointGraphics->getId(), checkpointGraphics);
        }

        checkpointGraphics->setPos(iterCheckpoint->getX(), iterCheckpoint->getY());
    }


    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(mView);
    setLayout(layout);

    qDebug() << "Topic recu = " << MqttService::instance();
    qDebug() << "Topic width = " << Map::getInstance()->getMapWidth();
    qDebug() << "Topic recu = " << Map::getInstance()->getMapHeight();

}

void Widget::updateProperties() {
    ObstacleGraphics::heigth = Properties::getInstance()->getRectangleHeight();
    ObstacleGraphics::width = Properties::getInstance()->getRectangleWidth();
    ObstacleGraphics::radius = Properties::getInstance()->getCircleRadius();
}

void Widget::updateGameMode() {

    for (Player *iterPlayer : GameMode::getInstance()->_players->values()) {
        PlayerGraphics *playerGraphics = localPlayers.value(iterPlayer->getUuid());

        if (!playerGraphics) {
            playerGraphics = new PlayerGraphics(iterPlayer);
            playerGraphics->setPos(playerGraphics->getX(), playerGraphics->getY());

            mScene->addItem(playerGraphics);
            localPlayers.insert(playerGraphics->getUuid(), playerGraphics);
        }

        playerGraphics->setPos(playerGraphics->getX(), playerGraphics->getY());
    }
}
