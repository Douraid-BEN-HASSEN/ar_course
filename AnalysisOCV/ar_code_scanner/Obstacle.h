#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

class Obstacle : public QObject
{
    Q_OBJECT
public:
    // constructor
    explicit Obstacle(QObject *parent = nullptr);
    // destructor
    ~Obstacle();

    // === UTILS ===
    void deserialize(const QJsonObject &json);
    QString serialize();
    QJsonObject toJson();

    // === SETTER ===
    void setId(int pId);
    void setX(int pX);
    void setY(int pY);
    void setAngle(float pAngle);

    // === GETTER ===
    int getId();
    int getX();
    int getY();
    float getAngle();

private:
    int _id;
    int _x;
    int _y;
    float _angle;

signals:

};

#endif // OBSTACLE_H
