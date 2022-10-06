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
    GPlayer(Player *, QGraphicsItem *parent = nullptr);

    static QString type;

    QString getUuid();
    QPoint getPos();
    float getAngle();
    qreal getRadius();
    void setHeigth(int);
    void setWidth(int);
    void setAngle(float);

    QString className();
    void update(Control *control);
    Player* getPlayer();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QString uuid;
    qreal heigth = 50;
    qreal width = 50;
    int _speed = 0;

    Player *_player;
    float _angle = 0;
    QString _vehicle;
    QMap<QString, int> *_items;
    int _lastCheckpoint = 0;
    int _currentLap = 0;
    QString _status;
    QString _controller;
    QPointF _vitesse;
};

#endif // GPLAYER_H
