#include "PlayerScoreItem.h"

PlayerScoreItem::PlayerScoreItem(GPlayer *g_player, QWidget *parent): QFrame{parent}
{
    setLayout(new QHBoxLayout());

    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setFixedSize(450, 40);

    setFrameStyle(QFrame::Panel | QFrame::Raised);
    setStyleSheet("QFrame {background-color: rgb(255, 255, 255);"
                                    "border-width: 1;"
                                    "border-style: solid;"
                                    "border-color: rgb(0, 0, 0)}"
                                    );

    this->g_player = g_player;

    qDebug() << g_player->getTime();

    label_playerName = new QLabel(g_player->getPlayer()->getPseudo());
    label_lastCheckpoint = new QLabel(QString::number(g_player->getPlayer()->getLastCheckpoint()));
    label_currentLap = new QLabel(QString::number(g_player->getPlayer()->getCurrentLap()));
    label_controller = new QLabel(g_player->getPlayer()->getController());
    label_time = new QLabel(g_player->getTime().toString("m:ss:zzz"));
    label_state = new QLabel(g_player->getState());

    layout()->addWidget(label_playerName);
    layout()->addWidget(label_lastCheckpoint);
    layout()->addWidget(label_currentLap);
    layout()->addWidget(label_time);
    layout()->addWidget(label_state);
    layout()->addWidget(label_controller);

    connect(g_player->getPlayer(), SIGNAL(stateUpdated()), this, SLOT(updateWidget()));
    connect(g_player, SIGNAL(stateUpdated()), this, SLOT(updateWidget()));
}


void PlayerScoreItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    updateWidget();
}

void PlayerScoreItem::updateWidget()
{


    if (label_playerName->text() != this->g_player->getPlayer()->getPseudo()) {
        label_playerName->setText(this->g_player->getPlayer()->getPseudo());
    }

    if (label_playerName->text() != QString::number(g_player->getPlayer()->getLastCheckpoint())) {
        label_lastCheckpoint->setText(QString::number(g_player->getPlayer()->getLastCheckpoint()));
    }

    if (label_currentLap->text() != QString::number(g_player->getPlayer()->getCurrentLap())) {
        label_currentLap->setText(QString::number(g_player->getPlayer()->getCurrentLap()));
    }

    if (label_time->text() != g_player->getTime().toString("m:ss:zzz")) {
        label_time->setText(g_player->getTime().toString("m:ss:zzz"));
    }

    if (label_state->text() != g_player->getState()) {
        label_state->setText(g_player->getState());
    }

    if (label_controller->text() != g_player->getPlayer()->getController()) {
        label_controller->setText(g_player->getPlayer()->getController());
    }
}
