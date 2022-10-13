#ifndef GAMEMODE_H
#define GAMEMODE_H

#if defined(GAMEMODE_LIBRARY)
#  define GAMEMODE_EXPORT Q_DECL_EXPORT
#else
#  define GAMEMODE_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>

#include <Kart/Map/Map.h>
#include <Mqtt/MqttService.h>
#include <Kart/Game/Properties.h>
#include <Kart/Game/Control.h>
#include <Kart/Game/Vehicle.h>
#include <algorithm>
#include <QTimer>
#include <Kart/Player/Register.h>

#include "Player.h"
#include "Item.h"

class GAMEMODE_EXPORT GameMode: public QObject
{
    Q_OBJECT
public:
    static GameMode *getInstance();

    // constructor
    explicit GameMode(QObject *parent = nullptr);
    // desctructor
    ~GameMode();

    const QString topic = "game";

    QMap<QString, Player*> *_players;
    QMap<QString, Item*> *_items;

    // === UTILS ===
    void publish();
    void deserialize(const QJsonObject &);
    QString serialize();
    QJsonObject toJson();

    // === SETTER ===
    void setElapsedTime(int pElapsedTime);
    void setInfoMessage(QString pInfoMessage);
    void setStatus(QString pStatus);

    // === GETTER ===
    int getElapsedTime();
    QString getInfoMessage();
    QString getStatus();

    void reset();

private:

    int _elapsedTime;
    QString _infoMessage;
    QString _status;

public slots:
    void receivedMessage(QJsonObject pMessage, QString pTopic);

public: signals:
    void updated();

};

#endif // GAMEMODE_H
