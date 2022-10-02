#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent): QMainWindow(parent), ui(new Ui::Window)
{
    this->setWindowTitle("IA");
    ui->setupUi(this);

    MapWidget *mapWidget = new MapWidget;
    ui->verticalLayout_map->addWidget(mapWidget);

    connect(ui->pushButton_start, SIGNAL(clicked()), this, SLOT(startIA()));
}

Window::~Window()
{
    delete ui;
}

void Window::startIA()
{
    qDebug() << "start";
    QString pseudo = this->ui->lineEdit_Player->text();
    Register *r = new Register(pseudo, "ia", "car", 0, this);

    IA *ia = new IA(r);

    ia->setRegister(r);
    r->publish();
    this->ia = ia;

    ui->pushButton_start->setDisabled(true);
}
