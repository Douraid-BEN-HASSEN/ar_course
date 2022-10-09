#include "PlayerScoreItem.h"

PlayerScoreItem::PlayerScoreItem(Player *player, QWidget *parent): QWidget{parent}
{
    setLayout(new QHBoxLayout());

    this->player = player;

    label_playerName = new QLabel(player->getPseudo());
    label_lastCheckpoint = new QLabel(QString::number(player->getLastCheckpoint()));
    label_currentLap = new QLabel(QString::number(player->getCurrentLap()));

    layout()->addWidget(label_playerName);
    layout()->addWidget(label_lastCheckpoint);
    layout()->addWidget(label_currentLap);

    connect(player, SIGNAL(stateUpdated()), this, SLOT(updateWidget()));
}


void PlayerScoreItem::paintEvent(QPaintEvent *event)
{
    qDebug() << "paintEvent";
    updateWidget();
}

void PlayerScoreItem::updateWidget()
{
    qDebug() << "paintEvent";

    if (label_playerName->text() != this->player->getPseudo()) {
        label_playerName->setText(this->player->getPseudo());
    }

    if (label_playerName->text() != QString::number(player->getLastCheckpoint())) {
        label_lastCheckpoint->setText(QString::number(player->getLastCheckpoint()));
    }

    if (label_currentLap->text() != QString::number(player->getCurrentLap())) {
        label_currentLap->setText(QString::number(player->getCurrentLap()));
    }
}
