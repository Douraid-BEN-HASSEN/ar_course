#include "EndGame.h"
#include "ui_EndGame.h"

EndGame::EndGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndGame)
{
    ui->setupUi(this);
}

EndGame::~EndGame()
{
    delete ui;
}

void EndGame::setScoreboard(QWidget *widget)
{
    scoreBoard = widget;
    //ui->verticalLayout_scorebord->widget();
    ui->verticalLayout_scorebord->addWidget(widget);
}

void EndGame::on_pushButton_clicked()
{
    //signal de fermeture -> reset fenetre de jeux
    //emit closeEndScore();
    close();

}

void EndGame::closeEvent(QCloseEvent *){
    emit closeEndScore();
    //close();
    //this->
    //this->popUpEnd->setScoreboard(ui->tabWidget_scoreboard);
    //popUpEnd->setModal(true);
}


