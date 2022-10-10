#ifndef PLAYERSCOREITEM_H
#define PLAYERSCOREITEM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

#include <QSizePolicy>

#include <Kart/Player/Player.h>

class PlayerScoreItem : public QFrame
{
    Q_OBJECT
public:
    explicit PlayerScoreItem(Player *player, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:

    QLabel *label_playerName;
    QLabel *label_lastCheckpoint;
    QLabel *label_currentLap;

    Player *player;

private slots:
    void updateWidget();

signals:

};

#endif // PLAYERSCOREITEM_H
