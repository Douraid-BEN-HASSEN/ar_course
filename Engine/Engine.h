#ifndef ENGINE_H
#define ENGINE_H

#define ENGINE_CYCLE 20
#define ENGINE_FREQUENCY 1000 / ENGINE_CYCLE

#include <QObject>

#include <Mqtt/MqttService.h>
#include <QVector2D>

#include <Kart/Player/Player.h>
#include <Kart/Player/GameMode.h>
#include <Kart/Game/Control.h>
#include <Kart/Game/Vehicle.h>
#include <Kart/Map/Map.h>
#include <Kart/Player/RegisterManager.h>
#include <Kart/Game/Control.h>

#include "2DGraphics/GEngine.h"

#include "2DGraphics/GBanana.h"
#include "2DGraphics/GBomb.h"
#include "2DGraphics/GRocket.h"

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = nullptr);
    ~Engine();
    GEngine *getGEngine();

    GameMode *getGameMode();
    Properties *getProperties();
    void startGame();
    QDateTime getGameStartAt() const;

public slots:
    void reset();
    void gameUpdate();

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

    void spawnItem(GItem *);
    void destoryItem(GItem *);
    void lifeCycleItem(GItem *);

    QMap<int, GCheckpoint*> checkpointsGraphics;
    QMap<int, GObstacle*> obstaclesGraphics;
    QMap<QString, GPlayer*> playersGraphics;
    QList<GItem*> itemsGraphics;

    QList<QGraphicsItem*> collision(GPlayer*);
    // retourne la valeur d'intersection entre 2 items
    qreal intersectionVal(QGraphicsItem* pItem1, QGraphicsItem* pItem2);

    // graphic
    GEngine *g_engine;
    QDateTime gameStartAt;

    bool gameStarted = false;

private slots:
    void receivedMessage(QJsonObject message, QString topic);
    void registered(Register *);
    void updateMap();
    void initProperties();

public: signals:
    void updated();
};

#endif // ENGINE_H
