#include "GameMode.h"

GameMode::GameMode(QObject *parent): QObject{parent}
{
    this->_players = new QList<Player>();
    this->_items = new QList<Item>();
}

void GameMode::setElapsedTime(int pElapsedTime)
{
    this->_elapsedTime=pElapsedTime;

}

void GameMode::setInfoMessage(QString pInfoMessage)
{
    this->_infoMessage=pInfoMessage;

}

void GameMode::setStatus(QString pStatus)
{
    this->_status= pStatus;

}

int GameMode::getElapsedTime()
{
    return _elapsedTime;

}

QString GameMode::getInfoMessage()
{
    return _infoMessage;

}

QString GameMode::getStatus()
{
    return _status;

}

void GameMode::message(QJsonObject pMessage, QString pTopic)
{
    //
    if (pTopic == "/map") {
        QJsonArray players = pMessage["players"].toArray();

        for(int iPlayer=0; iPlayer<players.count(); iPlayer++) {
            Player player;
            player.deserialize(players[iPlayer].toObject());
            this->_players->append(player);
        }

        QJsonArray items = pMessage["items"].toArray();

        for(int iItem=0; iItem<players.count(); iItem++) {
            Item item;
            item.deserialize(items[iItem].toObject());
            this->_items->append(item);
        }

        this->_elapsedTime = pMessage["elapsedtime"].toInt();
        this->_infoMessage = pMessage["infoMessage"].toString();
        this->_status = pMessage["status"].toString();
     }


}
