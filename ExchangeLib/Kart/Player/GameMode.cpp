#include "GameMode.h"

// constructor
GameMode::GameMode(QObject *parent): QObject{parent}
{
    this->_players = new QList<Player*>();
    this->_items = new QList<Item*>();
    this->_mqtt = MqttService::instance();

    connect(this->_mqtt,
                SIGNAL(message(QJsonObject,QString)),
                this,
                SLOT(message(QJsonObject,QString)));

}

// destructor
GameMode::~GameMode() {
    delete this->_players;
    delete this->_items;
}

//  +-------+
//  | UTILS |
//  +-------+
void GameMode::deserialize(const QJsonObject &jsonObject)
{
    this->_players = new QList<Player*>();
    this->_items = new QList<Item*>();

    QJsonArray jsonPlayers = jsonObject["players"].toArray();

    foreach(const QJsonValue &value, jsonPlayers) {
        QJsonObject playerJsonObject = value.toObject();
        Player *player = new Player();
        player->deserialize(playerJsonObject);
        this->_players->append(player);
    }

    QJsonArray jsonItems = jsonObject["items"].toArray();

    foreach(const QJsonValue &value, jsonItems) {
        QJsonObject itemJsonObject = value.toObject();
        Item *item = new Item();
        item->deserialize(itemJsonObject);
        this->_items->append(item);
    }

    this->_elapsedTime = jsonObject["elapsedTime"].toInt();
    this->_infoMessage = jsonObject["infoMessage"].toString();
    this->_status = jsonObject["status"].toString();
}

QString GameMode::serialize()
{
    QJsonDocument doc(this->toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}

QJsonObject GameMode::toJson()
{
    QJsonObject jsonObject;

    auto playersJA = QJsonArray();
    auto itemsJA = QJsonArray();

    for (auto & player : *this->_players)
        playersJA.append(player->toJson());

    jsonObject["players"] = playersJA;

    for (auto & item : *this->_items)
        itemsJA.append(item->toJson());

    jsonObject["items"] = itemsJA;

    jsonObject["elapsedTime"] = this->_elapsedTime;
    jsonObject["infoMessage"] = this->_infoMessage;
    jsonObject["status"] = this->_status;

    return jsonObject;
}

//  +--------+
//  | SETTER |
//  +--------+
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

//  +--------+
//  | GETTER |
//  +--------+
int GameMode::getElapsedTime()
{
    return this->_elapsedTime;
}

QString GameMode::getInfoMessage()
{
    return this->_infoMessage;
}

QString GameMode::getStatus()
{
    return this->_status;
}

void GameMode::traitement()
{

}

//  +------+
//  | SLOT |
//  +------+
void GameMode::message(QJsonObject pMessage, QString pTopic)
{
    if (pTopic == "/map") this->deserialize(pMessage);
    qDebug() << "message";
}
