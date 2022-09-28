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
    explicit GameMode(QObject *parent = nullptr);

    void setElapsedTime(int pElapsedTime);
    void setInfoMessage(QString pInfoMessage);
    void setStatus(QString pStatus);

    int getElapsedTime();
    QString getInfoMessage();
    QString getStatus();

private:
    QList<Player> *_players;
    QList<Item> *_items;

    int _elapsedTime;
    QString _infoMessage;
    QString _status;

public slots:
    void message(QJsonObject pMessage, QString pTopic);

signals:

};

#endif // GAMEMODE_H
