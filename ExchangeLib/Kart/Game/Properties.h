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
    static Properties *getInstance();
    explicit Properties(QObject *parent = nullptr);

    const QString topic = "game/properties";

    QMap<QString, Vehicle *> *vehicleOptions = new QMap<QString, Vehicle *>;

    void deserialize(const QJsonObject &);
    QString serialize();
    QJsonObject toJson();

private:

    int laps = 0;
    int team = 0;

    int banana = 0;
    int bananaCooldown = 0;
    int bananaTTL = 0;
    int bananaRadius = 0;

    int bomb = 0;
    int bombCooldown = 0;
    int bombTTL = 0;
    int bombRadius = 0;
    int bombExplosionRadius = 0;

    int rocket = 0;
    int rocketCooldown = 0;
    float rocketSpeed = 0.0f;
    int rocketRadius = 0;

    int circleRadius = 0;
    int rectangleWidth = 0;
    int rectangleHeight = 0;
    int checkpointRadius = 0;

public:
    int getLaps() const;
    void setLaps(int laps);

    int getTeam() const;
    void setTeam(int team);

    int getBanana() const;
    void setBanana(int banana);

    int getBananaCooldown() const;
    void setBananaCooldown(int bananaCooldown);

    int getBananaTtl() const;
    void setBananaTtl(int bananaTtl);

    int getBananaRadius() const;
    void setBananaRadius(int bananaRadius);

    int getBomb() const;
    void setBomb(int bomb);

    int getBombCooldown() const;
    void setBombCooldown(int bombCooldown);

    int getBombTtl() const;
    void setBombTtl(int bombTtl);

    int getBombRadius() const;
    void setBombRadius(int bombRadius);

    int getBombExplosionRadius() const;
    void setBombExplosionRadius(int bombExplosionRadius);

    int getRocket() const;
    void setRocket(int rocket);

    int getRocketCooldown() const;
    void setRocketCooldown(int rocketCooldown);

    float getRocketSpeed() const;
    void setRocketSpeed(float rocketSpeed);

    int getRocketRadius() const;
    void setRocketRadius(int rocketRadius);

    int getCircleRadius() const;
    void setCircleRadius(int circleRadius);

    int getRectangleWidth() const;
    void setRectangleWidth(int rectangleWidth);

    int getRectangleHeight() const;
    void setRectangleHeight(int rectangleHeight);

    int getCheckpointRadius() const;
    void setCheckpointRadius(int checkpointRadius);

private slots:
    void receivedMessage(QJsonObject message, QString topic);

public: signals:
    void updated();

};

#endif // PROPERTIES_H
