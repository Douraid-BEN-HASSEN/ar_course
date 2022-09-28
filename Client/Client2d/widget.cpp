#include "widget.h"
#include "ui_widget.h"

#include <QHBoxLayout>
#include "obstaclegraph.h"
#include "checkpointgraph.h"

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
    connect(Field::instance(), SIGNAL(fieldUpadeted()), this, SLOT(updateMap()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateMap(){

    //new QMap<int, Obstacle*>();
    // Faire une boucle sur tous les obstacles
    // Sur chaque obstacle on va devoir le créer + le placer


    for (auto * iter : Field::instance()->obstacles->values()) {
        // Verifier si l object ObstacleRect* obstaclerect  existe
        ObstacleGraph* obstaclegraph = new ObstacleGraph(iter);
        mScene->addItem(obstaclegraph);
        obstaclegraph->setPos(iter->x, iter->y);
    }


    for (auto * iter : Field::instance()->checkpoints->values()) {
         //Verifier si l object Checkpointgraph* obstaclerect  existe
        Checkpointgraph* checkpointgraph = new Checkpointgraph(iter);
        mScene->addItem(checkpointgraph);
        checkpointgraph->setPos(iter->x, iter->y);
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
    qDebug() << "Topic width = " << Field::instance()->width;
    qDebug() << "Topic recu = " << Field::instance()->height;

}

