#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include <QJsonObject>

class Obstacle : public QObject
{
    Q_OBJECT
public:
    explicit Obstacle(QObject *parent = nullptr);

    int id;
    int x;
    int y;
    float angle;

    void deserialize(const QJsonObject &json);
signals:

};

#endif // OBSTACLE_H
