#include "widget.h"
#include "ui_widget.h"

#include <QHBoxLayout>
#include "obstaclerect.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mScene = new QGraphicsScene(this);
    mScene->setSceneRect(0,0,1000,1000);
    mView = new QGraphicsView(this);

    mView->setScene(mScene);

    QGraphicsRectItem* rectItem = new QGraphicsRectItem(0,0,50,50);
    rectItem->setBrush(Qt::red);
    mScene->addItem(rectItem);
    rectItem->setPos(200,200);

    obstacleRect* o21 = new obstacleRect();

    mScene->addItem(o21);
    o21->setPos(300,300);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(mView);
    setLayout(layout);

}

Widget::~Widget()
{
    delete ui;
}

