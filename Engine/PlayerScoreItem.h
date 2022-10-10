#ifndef PLAYERSCOREITEM_H
#define PLAYERSCOREITEM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

#include <QSizePolicy>

#include "2DGraphics/GPlayer.h"

class PlayerScoreItem : public QFrame
{
    Q_OBJECT
public:
    explicit PlayerScoreItem(GPlayer *g_player, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:

    QLabel *label_playerName;
    QLabel *label_lastCheckpoint;
    QLabel *label_currentLap;
    QLabel *label_controller;
    QLabel *label_time;
    QLabel *label_state;

    GPlayer *g_player;

private slots:
    void updateWidget();

signals:

};

#endif // PLAYERSCOREITEM_H
