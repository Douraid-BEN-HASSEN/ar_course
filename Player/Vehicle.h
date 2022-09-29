#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>

class Vehicle : public QObject
{
    Q_OBJECT
public:
    explicit Vehicle(QObject *parent = nullptr);

    int maxSpeed = 0;
    float acceleration = 0.0f;
    int weight = 0.0f;
    float steeringAngle = 0.0f;
    QString type = "";


    Vehicle(int maxSpeed, float acceleration , int weight , float steeringAngle , QString type);
    void deserialize(const QJsonObject &);
    QString serialize();
    QJsonObject toJson();

signals:

};

#endif // VEHICLE_H

