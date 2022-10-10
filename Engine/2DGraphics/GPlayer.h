#ifndef GPLAYER_H
#define GPLAYER_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>

#include <Kart/Player/Player.h>
#include <Kart/Game/Properties.h>

class GPlayer: public QGraphicsObject
{
    Q_OBJECT
public:
    // === constructor ===
    GPlayer(Player *, QGraphicsItem *parent = nullptr);

    static QString type;

    // === GETTER ===
    QString getUuid();
    QPoint getPos();
    float getAngle();
    qreal getRadius();
    int getBananaCooldown();
    int getBombCooldown();
    int getRocketCooldown();
    int getnBanana();
    int getnRocket();
    int getnBomb();

    // === SETTER ====
    void setHeigth(int);
    void setWidth(int);
    void setAngle(float);
    void setBananaCooldown(int pBananaCooldown);
    void setBombCooldown(int pBombCooldown);
    void setRocketCooldown(int pRockerCooldown);
    void setnBanana(int pnBanana);
    void setnBomb(int pnBomb);
    void setnRocket(int pnRocket);
    void setVitesse(QVector2D vectorSpeed);

    QString getState();
    void setState(QString);

    QTime getTime();
    void setTime(QTime);

    void hit();

    QString className();
    void update(Control *control);
    Player* getPlayer();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QString uuid;
    qreal heigth = 50;
    qreal width = 50;
    int _stunt = 0;

    Player *_player;
    float _angle = 0;
    QString _vehicle;
    QMap<QString, int> *_items;
    int _lastCheckpoint = 0;
    int _currentLap = 0;
    QString _status;
    QString _controller;
    QVector2D _vitesse;
    QTime timeLaps = QTime(0, 0, 0, 0);
    QString state = "wait";

    //
    int _nBanane;
    int _nBomb;
    int _nRocket;

    // items cooldown
    int _bananaCooldown;
    int _bombCooldown;
    int _rocketCooldown;

public: signals:
    void stateUpdated();

};

#endif // GPLAYER_H
