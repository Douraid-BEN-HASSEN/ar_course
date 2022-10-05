#ifndef ENGINE_H
#define ENGINE_H

#include "Kart/Game/Control.h"
#include <QObject>

#include <Mqtt/MqttService.h>

#include <Kart/Player/Player.h>
#include <Kart/Player/GameMode.h>
#include <Kart/Game/Control.h>
#include <Kart/Game/Vehicle.h>
#include <Kart/Map/Map.h>
#include <Kart/Player/RegisterManager.h>

#include "GEngine.h"

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = nullptr);
    ~Engine();
    GEngine *getGEngine();

private:
    MqttService *_mqtt;

    QMap<QString, Control*> *_controls;
    Map *_map;
    GameMode *_gameMode;
    Properties *_properties;

    void traitementPlayerRegister(QJsonObject pMessage);
    void traitementPlayerControl(QJsonObject pMessage);

    void envoiGameProperties();
    void envoiGameInfo();
    void control_th();
    int getNextCheckpointId(int pCurrentCheckpoint);

    QMap<int, GCheckpoint*> checkpointsGraphics;
    QMap<int, GObstacle*> obstaclesGraphics;
    QMap<QString, GPlayer*> playersGraphics;

    QList<QGraphicsItem*> collision(GPlayer*);
    // retourne la valeur d'intersection entre 2 items
    qreal intersectionVal(QGraphicsItem* pItem1, QGraphicsItem* pItem2);

    // graphic
    GEngine *g_engine;

private slots:
    void receivedMessage(QJsonObject message, QString topic);
    void registered(Register *);
    void updateMap();

};

#endif // ENGINE_H
