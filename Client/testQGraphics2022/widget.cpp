#include "widget.h"
#include "ui_widget.h"

#include <QHBoxLayout>
#include "obstaclerect.h"

#include "Mqtt/MqttService.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mScene = new QGraphicsScene(this);
    mScene->setSceneRect(Field::instance()->width,Field::instance()->width,Field::instance()->height,Field::instance()->height);
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
       // ObstacleRect* obstaclerect = new ObstacleRect(new Obstacle());
        ObstacleRect* obstaclerect = new ObstacleRect(1, 1, 1, 1);
    }


    for (auto iter = Field::instance()->obstacles->constBegin(); iter != Field::instance()->obstacles->constEnd(); ++iter) {
        ObstacleRect* obstaclerect = new ObstacleRect();



        QGraphicsSimpleTextItem* idObstacle = new QGraphicsSimpleTextItem(QString::number(iter.value()->id));
        qDebug() << "value()->id) = " << iter.value()->id;
        idObstacle->setBrush(Qt::black);
        idObstacle->setPos(iter.value()->x+25,iter.value()->y+25);
        if(iter.value()->id % 2 == 1){
            QGraphicsRectItem* rectItem = new QGraphicsRectItem(0,0,50,50);
            rectItem->setBrush(Qt::red);
            mScene->addItem(rectItem);
            rectItem->setPos(iter.value()->x,iter.value()->y);
        } else {
            QGraphicsEllipseItem* ellipseItemObstacle = new QGraphicsEllipseItem(0,0,50,50);
            ellipseItemObstacle->setBrush(Qt::red);
            mScene->addItem(ellipseItemObstacle);
            ellipseItemObstacle->setPos(iter.value()->x,iter.value()->y);
        }
        mScene->addItem(idObstacle);

    }


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




    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(mView);
    setLayout(layout);


    qDebug() << "Topic recu = " << MqttService::instance();
    qDebug() << "Topic width = " << Field::instance()->width;
    qDebug() << "Topic recu = " << Field::instance()->height;

}

