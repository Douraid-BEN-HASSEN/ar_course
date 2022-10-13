#include "EndGameDialog.h"
#include "ui_EndGameDialog.h"

EndGameDialog::EndGameDialog(QWidget *parent): QDialog(parent),
    ui(new Ui::EndGameDialog)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(closeDialog()));
}

EndGameDialog::~EndGameDialog()
{
    delete ui;
}

void EndGameDialog::setScoreboard(QWidget *widget)
{
    ui->verticalLayout_scorebord->addWidget(widget);
}

void EndGameDialog::closeDialog()
{
    this->close();
}

void EndGameDialog::closeEvent(QCloseEvent *){
    emit closed();
}



