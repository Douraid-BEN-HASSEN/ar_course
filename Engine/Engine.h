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
#include "2DGraphics/widget.h"

#include "GEngine.h"

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = nullptr);
    ~Engine();

private:
    MqttService *_mqtt;

    //QMap<QString, Player*> *_players; // enlver et mettre la qmpa de gamemode
    QMap<QString, Control*> *_controls;
    Map *_map;
    GameMode *_gameMode;
    Properties *_properties;


    void traitementPlayerRegister(QJsonObject pMessage);
    void traitementPlayerControl(QJsonObject pMessage);

    void envoiGameInfo();
    void control_th();
    int getNextCheckpointId(int pCurrentCheckpoint);

    // graphic
    GEngine g_engine;

    Checkpoint *testCheckpoint;
    Obstacle *testObstacle;
    Player *testPlayer;

private slots:
    void receivedMessage(QJsonObject message, QString topic);

};

#endif // ENGINE_H
