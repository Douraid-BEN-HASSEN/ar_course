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

#include "Player.h"
#include "Item.h"
#include <Kart/Map/Map.h>
#include <Mqtt/MqttService.h>
#include <Kart/Game/Properties.h>
#include <Kart/Game/Control.h>
#include <QTimer>
#include <Kart/Game/Vehicle.h>



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

private:
    Properties *_properties;
    QMap<QString,Player*> *_players;
    QList<Item*> *_items;

    int _elapsedTime;
    QString _infoMessage;
    QString _status;

public slots:
    void receivedMessage(QJsonObject pMessage, QString pTopic);

public: signals:
    void mapUpadeted();

};

#endif // GAMEMODE_H
