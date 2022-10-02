#include "GameMode.h"

GameMode *GameMode::getInstance() {
    static GameMode *instance;

    if (instance == nullptr) {
        qDebug() << "new instance GameMode";
        instance = new GameMode();

        MqttService::instance()->subscribe(instance->topic);

        /* -- connect -- */
        /* todo implmente an interface and methode to connect */
        connect(MqttService::instance(), &MqttService::message, instance, &GameMode::receivedMessage);
    }

    return instance;
}

// constructor
GameMode::GameMode(QObject *parent): QObject{parent}
{   
    this->_players = new QMap<QString, Player*>();
    this->_items = new QList<Item*>();

    this->_elapsedTime = 0;
    this->_infoMessage = "Init";
    this->_status = "Init";
}

// destructor
GameMode::~GameMode() {
    delete this->_players;
    delete this->_items;
}

void GameMode::publish() {
    MqttService::instance()->publish(GameMode::topic, this->serialize().toUtf8());
}

//  +-------+
//  | UTILS |
//  +-------+
void GameMode::deserialize(const QJsonObject &jsonObject)
{
    this->_players = new QMap<QString, Player*>();
    this->_items = new QList<Item*>();

    QJsonArray jsonPlayers = jsonObject["players"].toArray();

    for(const QJsonValue &value: jsonPlayers) {
        QJsonObject playerJsonObject = value.toObject();
        Player *player = this->_players->value(playerJsonObject["uuid"].toString());

        if (!player) {
            player = new Player();
        }

        player->deserialize(playerJsonObject);
        this->_players->insert(player->getUuid(), player);
    }

    QJsonArray jsonItems = jsonObject["items"].toArray();

    for(const QJsonValue &value: jsonItems) {
        QJsonObject itemJsonObject = value.toObject();
        Item *item = new Item();
        item->deserialize(itemJsonObject);
        this->_items->append(item);
    }

    this->_elapsedTime = jsonObject["elapsedTime"].toInt();
    this->_infoMessage = jsonObject["infoMessage"].toString();
    this->_status = jsonObject["status"].toString();

    emit updated();
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

void GameMode::receivedMessage(QJsonObject message, QString topic) {
    if (topic == GameMode::topic) {
        this->deserialize(message);
    }
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
