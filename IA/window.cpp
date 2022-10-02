#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent): QMainWindow(parent), ui(new Ui::Window)
{
    ui->setupUi(this);
    MapWidget *mapWidget = new MapWidget;
    ui->verticalLayout_main->addWidget(mapWidget);
}

Window::~Window()
{
    delete ui;
}

