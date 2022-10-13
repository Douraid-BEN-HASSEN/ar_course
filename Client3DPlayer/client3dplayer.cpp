#include "client3dplayer.h"

void Client3DPlayer::onRunFind()
{
    qDebug() << "Run Find" ;
    this->container_widget_3d->setVisible(true);
}

Client3DPlayer::Client3DPlayer(QWidget *parent)
    : QWidget(parent)
{

    //Init objects

    this->player_ui = new PlayerUi(this) ;
    this->widget_3d = new Widget3D();

    //Init ui
    this->main_layout = new QVBoxLayout ;

    this->visuel_layout = new QHBoxLayout ;

    this->container_widget_3d = QWidget::createWindowContainer(this->widget_3d);
    this->container_widget_3d->setFixedSize(QSize(1200,750));
    this->visuel_layout->addWidget(this->container_widget_3d);

    this->playerInterface_layout = new QHBoxLayout ;
    this->playerInterface_layout->addWidget(this->player_ui);


    this->main_layout->addLayout(this->visuel_layout);
    this->main_layout->addLayout(this->playerInterface_layout);

    setLayout(this->main_layout);

    container_widget_3d->setVisible(false);

    //Connect
    makeConnect() ;
}

void Client3DPlayer::makeConnect() {
    connect(this->player_ui , SIGNAL(onRegisterButtonClick()) , this , SLOT(onRunFind()));
}
Client3DPlayer::~Client3DPlayer()
{
}


