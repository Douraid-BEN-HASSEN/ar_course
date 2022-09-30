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
    explicit Vehicle(QObject *parent = nullptr);
    Vehicle(int maxSpeed, float acceleration , int weight , float steeringAngle , QString type, QObject *parent = nullptr);
    Vehicle(QString type, QObject *parent = nullptr);

    // === GETTER ===
    float getMaxSpeed();
    float getAcceleration();
    float getWeight();
    float getSteeringAngle();
    int getWidth();
    int getHeight();

    QString toString();

    void deserialize(const QJsonObject &);
    QString serialize();
    QJsonObject toJson();

    void setType(QString type);
    QString getType() ;

private:
    int maxSpeed = 0;
    float acceleration = 0.0f;
    int weight = 0.0f;
    float steeringAngle = 0.0f;
    int width = 0;
    int height = 0;

    QString type;

signals:

};

#endif // VEHICLE_H
