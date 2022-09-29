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


class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = nullptr);

private:
    MqttService *_mqtt;

    QMap<QString, Player*> *_players;
    QMap<QString, Control*> *_controls;
    Map *_map;
    GameMode *_gameMode;


    void traitementPlayerRegister(QJsonObject pMessage);
    void traitementPlayerControl(QJsonObject pMessage);

    void envoiGameInfo();
    void control_th();



private slots:
    void receivedMessage(QJsonObject message, QString topic);

};

#endif // ENGINE_H
