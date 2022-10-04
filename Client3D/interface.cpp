#include "interface.h"
#include "ui_interface.h"

interface::interface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::interface)
{
    ui->setupUi(this);
    Widget *widget = new Widget;
    ui->verticalLayout->addWidget(widget);
}

interface::~interface()
{
    delete ui;
}

