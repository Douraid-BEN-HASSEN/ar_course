#ifndef PROPERTIES_H
#define PROPERTIES_H

#if defined(PROPERTIES_LIBRARY)
#  define PROPERTIES_EXPORT Q_DECL_EXPORT
#else
#  define PROPERTIES_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>
#include <QMap>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <Mqtt/MqttService.h>

#include "Vehicle.h"

class PROPERTIES_EXPORT Properties : public QObject {
    Q_OBJECT
public:
    explicit Properties(QObject *parent = nullptr);

    const QString topic = "/game/properties";

    int laps = 0;
    int team = 0;
    float circleRadius = 0.0f;
    float rectangleWidth = 0.0f;
    float rectangleHeight = 0.0f;
    float checkpointRadius = 0.0f;

    int banana = 0;
    int bomb = 0;
    int rocket = 0;

    int bananaCooldown = 0;
    int bombCooldown = 0;
    int rocketCooldown = 0;

    float rocketSpeed = 0.0f;
    int bananaTTL = 0.0f;
    int bombTTL = 0.0f;

    QMap<QString, Vehicle *> *vehicleOptions = new QMap<QString, Vehicle *>;

    void deserialize(const QJsonObject &);
    QString serialize();
    QJsonObject toJson();

signals:

private slots:
    void receivedMessage(QJsonObject message, QString topic);
};

#endif // PROPERTIES_H
