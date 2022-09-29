#ifndef VEHICLE_H
#define VEHICLE_H

#if defined(VEHICLE_LIBRARY)
#  define VEHICLE_EXPORT Q_DECL_EXPORT
#else
#  define VEHICLE_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>

class VEHICLE_EXPORT Vehicle : public QObject
{
    Q_OBJECT
public:
    Vehicle(int maxSpeed, float acceleration , int weight , float steeringAngle , QString type, QObject *parent = nullptr);
    Vehicle(QString type, QObject *parent = nullptr);


    QString toString();

    void deserialize(const QJsonObject &);
    QString serialize();
    QJsonObject toJson();

    // === GETTER ===
    float getMaxSpeed();
    float getAcceleration();
    float getWeight();
    float getSteeringAngle();
    int getWidth();
    int getHeight();

private:
    int maxSpeed;
    float acceleration;
    float weight;
    float steeringAngle;
    int width;
    int height;

    QString type;

signals:

};

#endif // VEHICLE_H
