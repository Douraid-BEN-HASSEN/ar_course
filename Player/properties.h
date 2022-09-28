#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QObject>
#include <QMap>
#include "vehicle.h"

class Properties : public QObject
{
    Q_OBJECT
public:
    explicit Properties(QObject *parent = nullptr);
    int lapsNb = 0;
    int teamNb = 0;
    float circleRadius = 0.0f;
    float rectangleWidth = 0.0f;
    float rectangleHeight = 0.0f;
    float checkpointRadius = 0.0f;

    int bananaNb = 0;
    int bombNb = 0;
    int rocketNb = 0;

    int bananaCd = 0;
    int bombCd = 0;
    int rocketCd = 0;

    float rocketSpeed = 0.0f;
    int bananaTtL = 0.0f;
    int bombTtL = 0.0f;

    QList<Vehicle*> * vehicleOptions = new  QList<Vehicle*>;

    void deserialize(const QJsonObject &);
    QString serialize();
    QJsonObject toJson();

signals:

};

#endif // PROPERTIES_H
