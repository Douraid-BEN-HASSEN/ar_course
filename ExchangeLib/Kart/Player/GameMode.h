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

class GAMEMODE_EXPORT GameMode: public QObject
{
    Q_OBJECT
public:
    // constructor
    explicit GameMode(QObject *parent = nullptr);
    // desctructor
    ~GameMode();

    // === UTILS ===
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
    Map *_map;
    QMap<QString,Player*> *_players;
    QList<Item*> *_items;

    int _elapsedTime;
    QString _infoMessage;
    QString _status;
    MqttService *_mqtt;

    void traitement();
    void traitementMap(QJsonObject pMessage);
    void traitementPlayerRegister(QJsonObject pMessage);
    void traitementPlayerControl(QJsonObject pMessage);

public slots:
    void message(QJsonObject pMessage, QString pTopic);

signals:

};

#endif // GAMEMODE_H
