#ifndef GPLAYER_H
#define GPLAYER_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>

#include <Kart/Player/Player.h>

class GPlayer: public QGraphicsObject
{
    Q_OBJECT
public:
    GPlayer(Player *, QGraphicsItem *parent = nullptr);

    static QString type;

    QString getUuid();
    QPoint getPos();
    qreal getRadius();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    Player* getPlayer();
    QString className();
    void update(Control *control);



private:
    QString uuid;
    qreal heigth = 50;
    qreal width = 50;
    Player *_player;
    float _angle = 0;
    int _speed = 0;
    QString _vehicle;
    QMap<QString, int> *_items;
    int _lastCheckpoint = 0;
    int _currentLap = 0;
    QString _status;
    QString _controller;
    QPointF _vitesse;
};

#endif // GPLAYER_H
