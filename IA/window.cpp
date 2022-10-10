#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent): QMainWindow(parent), ui(new Ui::Window)
{
    qDebug() << "Window::Window" ;

    this->setWindowTitle("IA");
    ui->setupUi(this);
    MapWidget *mapWidget = new MapWidget;

    connect(this, SIGNAL(drawPath(QList<QPair<QString, Checkpoint *>>)), mapWidget, SLOT(drawPath(QList<QPair<QString, Checkpoint *>>)));

    ui->verticalLayout_map->addWidget(mapWidget);

    //Connect
    connect(ui->pushButton_start, SIGNAL(clicked()), this, SLOT(startIA()));
}

Window::~Window()
{
    delete ui;
}

void Window::startIA()
{

    qDebug() << "Window::startIa()";

    if ( this->ui->lineEdit_Player->text() != "" && this->ui->lineEdit_Speed->text() != " " ) {
        QString pseudo = this->ui->lineEdit_Player->text();
        Register *r = new Register(pseudo, "ia", "car", 0, this);p
        IA *ia = new IA(r , (int)this->ui->lineEdit_Speed->text().toInt());
        connect(ia, SIGNAL(determinePathDone(QList<QPair<QString , Checkpoint*>>)), this, SLOT(getPath(QList<QPair<QString, Checkpoint *>>)));

        ia->setRegister(r);
        r->publish();


        this->ui->label_size->setText("height : " + QString::number(r->getVehicle().size()) );
        qDebug() << r->getVehicle() ;
        this->ia = ia;

        ui->pushButton_start->setDisabled(true);

       //
    }

}

void Window::getPath(QList<QPair<QString, Checkpoint *>> path) {
    emit this->drawPath(path);
}
