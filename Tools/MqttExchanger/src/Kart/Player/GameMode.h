#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <QObject>
#include <QList>
#include "Player.h"
#include "Item.h"
#include <QJsonObject>
#include <QJsonArray>
class GameMode : public QObject
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
    QList<Player*> *_players;
    QList<Item*> *_items;

    int _elapsedTime;
    QString _infoMessage;
    QString _status;

    void traitementPhysics(); // méthode qui gère la la physique

public slots:
    void message(QJsonObject pMessage, QString pTopic);

signals:

};

#endif // GAMEMODE_H
