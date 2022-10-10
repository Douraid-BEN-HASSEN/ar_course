#ifndef LINE_H
#define LINE_H

#include <QGraphicsObject>
#include <QObject>
#include <QPainter>
#include <QBrush>


class Line: public QGraphicsObject
{
    Q_OBJECT
public:
    Line(QPoint p1, QPoint p2);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // === GETTER ===
    QPoint getP1();
    QPoint getP2();

    // === SETTER ===
    void setP1(QPoint p1);
    void setP2(QPoint p2);

private:
    QPoint _p1;
    QPoint _p2;
};

#endif // LINE_H
