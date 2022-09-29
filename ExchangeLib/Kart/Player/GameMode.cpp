#include "GameMode.h"

// constructor
GameMode::GameMode(QObject *parent): QObject{parent}
{
    this->_players = new QMap<QString, Player*>();
    this->_items = new QList<Item*>();
    this->_mqtt = MqttService::instance();
    this->_mqtt->subscribe("map");
    this->_mqtt->subscribe("player/register");
    this->_mqtt->subscribe("player/control");

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
    this->_players = new QMap<QString, Player*>();
    this->_items = new QList<Item*>();

    QJsonArray jsonPlayers = jsonObject["players"].toArray();

    foreach(const QJsonValue &value, jsonPlayers) {
        QJsonObject playerJsonObject = value.toObject();
        Player *player = new Player();
        player->deserialize(playerJsonObject);
        this->_players->insert(player->getUuid(), player);
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

void GameMode::traitementMap(QJsonObject pMessage)
{

}

void GameMode::traitementPlayerRegister(QJsonObject pMessage)
{
    Player *player = new Player();
    player->deserialize(pMessage);
    this->_players->insert(player->getUuid(), player);
}

void GameMode::traitementPlayerControl(QJsonObject pMessage)
{
/*
    "uuid": str,
    "angle": float, // en rad
    "power": int, // [-100%;100%]
    "buttons": { // état des boutons
    "banana": bool,
    "bomb": bool,
    "rocket": bool
    }
*/
    QString uuid = pMessage["uuid"].toString();

    Player *player = this->_players->value(uuid);

    if(!player) {
        qDebug() << "[ERROR] traitementPlayerControl player not found";
        return;
    }

    //calcul new data
    int newX;
    int newY;
    float newAngle;
    int newSpeed;

    //check checkpoint
    //bounded rect du checkpoint

}

//  +------+
//  | SLOT |
//  +------+
void GameMode::message(QJsonObject pMessage, QString pTopic)
{
    if (pTopic == "map") this->traitementMap(pMessage);
    if (pTopic == "player/register") this->traitementPlayerRegister(pMessage);
    if (pTopic == "player/control") this->traitementPlayerControl(pMessage);

    qDebug() << "message";
}


