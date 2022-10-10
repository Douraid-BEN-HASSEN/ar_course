#include "PlayerScoreItem.h"

PlayerScoreItem::PlayerScoreItem(Player *player, QWidget *parent): QFrame{parent}
{
    setLayout(new QHBoxLayout());

    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setFixedSize(280, 40);
//    setStyleSheet("border: 1px solid black");
    setFrameStyle(QFrame::Panel | QFrame::Raised);
    setStyleSheet("QFrame {background-color: rgb(255, 255, 255);"
                                    "border-width: 1;"
                                    "border-style: solid;"
                                    "border-color: rgb(0, 0, 0)}"
                                    );

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
    Q_UNUSED(event);

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
