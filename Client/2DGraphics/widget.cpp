#include "widget.h"
#include "ui_widget.h"

#include <QHBoxLayout>
#include "ObstacleGraphics.h"
#include "CheckpointGraphics.h"
#include "Kart/Map/Map.h"
#include "Kart/Game/Properties.h"

#include "Mqtt/MqttService.h"

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
    connect(Map::instance(), SIGNAL(mapUpadeted()), this, SLOT(updateMap()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateMap(){
    //new QMap<int, Obstacle*>();
    // Faire une boucle sur tous les obstacles
    // Sur chaque obstacle on va devoir le créer + le placer

    for (auto * iterObstacle : Map::instance()->getObstacles()->values()) {
        // Verifier si l object ObstacleRect* obstaclerect  exist

        // Rentrer dands le if si sa existe
        if(localObstacles.value(iterObstacle->getId())){
            localObstacles.value(iterObstacle->getId())->setPos(iterObstacle->getX(),iterObstacle->getY());
        } else {
            ObstacleGraphics* obstaclegraph = new ObstacleGraphics(iterObstacle);
            mScene->addItem(obstaclegraph);
            obstaclegraph->setPos(iterObstacle->getX(), iterObstacle->getY());
            localObstacles.insert(obstaclegraph->getId(),obstaclegraph);
        }
    }


    for (auto * iterCheckout : Map::instance()->getCheckpoints()->values()) {
        if(localCheckpoint.value(iterCheckout->getId())){
            qDebug() <<  "le checkpoint existe donc je dois vérifier la position";
            localCheckpoint.value(iterCheckout->getId())->setPos(iterCheckout->getX(),iterCheckout->getY());
        } else {
            CheckpointGraphics* checkpointgraph = new CheckpointGraphics(iterCheckout);
            mScene->addItem(checkpointgraph);
            checkpointgraph->setPos(iterCheckout->getX(), iterCheckout->getY());
            localCheckpoint.insert(checkpointgraph->getId(), checkpointgraph);
        }
    }


    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(mView);
    setLayout(layout);


    qDebug() << "Topic recu = " << MqttService::instance();
    qDebug() << "Topic width = " << Map::instance()->getMapWidth();
    qDebug() << "Topic recu = " << Map::instance()->getMapHeight();

}

