#include "window.h"
#include "ui_window.h"
#include <QPoint>

Window::Window(QWidget *parent): QMainWindow(parent), ui(new Ui::Window)
{
    qDebug() << "Window::Window" ;

    this->setWindowTitle("IA");
    ui->setupUi(this);
    MapWidget *mapWidget = new MapWidget;

    connect(this, SIGNAL(drawPath(QList<QPair<QString, Checkpoint *>>)), mapWidget, SLOT(drawPath(QList<QPair<QString, Checkpoint *>>)));

    ui->verticalLayout_map->addWidget(mapWidget);

    //Connect
    connect(ui->pushButton_calculPath, SIGNAL(clicked()), this, SLOT(calculPath()));
    connect(ui->pushButton_startIa, SIGNAL(clicked()) , this , SLOT(startIA()));
    ui->pushButton_startIa->setDisabled(true);

}


Window::~Window()
{
    delete ui;
}

void Window::calculPath(){

    qDebug() << "Window::calculPath()";

    QList<QPair<QString , Checkpoint*>> emptyList ;

    emit this->drawPath(emptyList);

    if ( this->ui->lineEdit_pseudo->text() != "" && this->ui->lineEdit_Speed->text() != "" && this->ui->lineEdit_Offset->text() != "" ) {
        QString pseudo = this->ui->lineEdit_pseudo->text();
        Register *r = new Register(pseudo, "ia", "car", 0, this);
        IA *ia = new IA(r , (int)this->ui->lineEdit_Speed->text().toInt() , (int)this->ui->lineEdit_Offset->text().toInt());
        connect(ia, SIGNAL(determinePathDone(QList<QPair<QString , Checkpoint*>>)), this, SLOT(getPath(QList<QPair<QString, Checkpoint *>>)));
        connect(ia , SIGNAL(changeTarget(QPoint)) , this , SLOT(changeLabelTarget(QPoint)));

        ia->setRegister(r);
        r->publish();

        this->ui->label_size->setText("height : " + QString::number(r->getVehicle().size()) );
        qDebug() << r->getVehicle() ;
        this->ia = ia;
        this->ui->pushButton_startIa->setDisabled(false);
    }
}

void Window::startIA()
{
    ui->pushButton_startIa->setDisabled(true);
    this->ia->mooveToCheckpoint();
}

void Window::changeLabelTarget(QPoint newTarget){
    qDebug() << "Window::changeLabelTarget(QPoint newTarget)" ;
    ui->label_targetPosition->setText("Target : "  + QString::number(newTarget.x()) + " ; " + QString::number(newTarget.y())) ;
}
void Window::getPath(QList<QPair<QString, Checkpoint *>> path) {
    emit this->drawPath(path);
}
