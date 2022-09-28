#ifndef OBSTACLERECT_H
#define OBSTACLERECT_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>

class obstacleRect : public QGraphicsObject
{
    Q_OBJECT
public:
    obstacleRect(QGraphicsItem *parent = nullptr);

    int id() const;

private:
    int mId;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // OBSTACLERECT_H
