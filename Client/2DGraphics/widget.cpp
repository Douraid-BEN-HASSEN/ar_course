#include "widget.h"
#include "ui_widget.h"

#include <QHBoxLayout>
#include "ObstacleGraphics.h"
#include "CheckpointGraphics.h"
#include "Kart/Map/Map.h"

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
    connect(Map::instance(), SIGNAL(fieldUpadeted()), this, SLOT(updateMap()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateMap(){

    //new QMap<int, Obstacle*>();
    // Faire une boucle sur tous les obstacles
    // Sur chaque obstacle on va devoir le créer + le placer


    for (auto * iter : Map::instance()->getObstacles()->values()) {
        // Verifier si l object ObstacleRect* obstaclerect  existe
        ObstacleGraphics* obstaclegraph = new ObstacleGraphics(iter);
        mScene->addItem(obstaclegraph);
        obstaclegraph->setPos(iter->getX(), iter->getY());
    }


    for (auto * iter : Map::instance()->getCheckpoints()->values()) {
         //Verifier si l object Checkpointgraph* obstaclerect  existe
        CheckpointGraphics* checkpointgraph = new CheckpointGraphics(iter);
        mScene->addItem(checkpointgraph);
        checkpointgraph->setPos(iter->getX(), iter->getY());
    }


/*
    for (auto iter = Field::instance()->checkpoints->constBegin(); iter != Field::instance()->checkpoints->constEnd(); ++iter) {
        QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem(0,0,50,50);
        QGraphicsSimpleTextItem* idCheckpoint = new QGraphicsSimpleTextItem(QString::number(iter.value()->id));
        ellipseItem->setBrush(Qt::yellow);
        idCheckpoint->setBrush(Qt::black);
        mScene->addItem(ellipseItem);
        mScene->addItem(idCheckpoint);
        ellipseItem->setPos(iter.value()->x,iter.value()->y);
        idCheckpoint->setPos(iter.value()->x+25,iter.value()->y+25);
    }
    */



    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(mView);
    setLayout(layout);


    qDebug() << "Topic recu = " << MqttService::instance();
    qDebug() << "Topic width = " << Map::instance()->getMapWidth();
    qDebug() << "Topic recu = " << Map::instance()->getMapHeight();

}

