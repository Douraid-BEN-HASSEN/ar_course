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

    int sizeObstacles = Field::instance()->obstacles->size();

    //new QMap<int, Obstacle*>();
    // Faire une boucle sur tous les obstacles
    // Sur chaque obstacle on va devoir le créer + le placer

/*
    for(int y = 0; y < sizeObstacles; y++){
       qDebug() << " obstacles = " << Field::instance()->obstacles->value(y)->x;
       qDebug() << " obstacles = " << Field::instance()->obstacles->value(y)->y;

       // Récupérer depuis /game/properties
       QGraphicsRectItem* rectItem = new QGraphicsRectItem(0,0,50,50);
       rectItem->setBrush(Qt::red);
       mScene->addItem(rectItem);
       rectItem->setPos(Field::instance()->obstacles->value(y)->x,Field::instance()->obstacles->value(y)->y);

   }
    */

    for (auto iter = Field::instance()->obstacles->constBegin(); iter != Field::instance()->obstacles->constEnd(); ++iter) {
        qDebug() << " obstacles = " << iter.value()->x;
        qDebug() << " obstacles = " << iter.value()->y;
        QGraphicsRectItem* rectItem = new QGraphicsRectItem(0,0,50,50);
        rectItem->setBrush(Qt::red);
        mScene->addItem(rectItem);
        rectItem->setPos(iter.value()->x,iter.value()->y);
    }

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(mView);
    setLayout(layout);

    qDebug() << "Topic recu = " << MqttService::instance();
    qDebug() << "Topic width = " << Field::instance()->width;
    qDebug() << "Topic recu = " << Field::instance()->height;

}

