#include "mqttservice.h"
#include "map.h"


MqttService *MqttService::instance()
{
    static MqttService instance;
    return &instance;
}


MqttService::MqttService(QObject *parent): QObject{parent}
{
    client = new QMqttClient();
    client->setHostname(Config.hostname);
    client->setPort(Config.port);
    client->setUsername(Config.username);
    client->setPassword(Config.password);

    subscribes = new QList<QMqttSubscription *>;

    /* -- connect -- */
    connect(client, &QMqttClient::stateChanged, this, &MqttService::stateChange);
    connect(client, &QMqttClient::messageReceived, this, &MqttService::receivedMessage);

    client->connectToHost();
}

void MqttService::sendMessageRegister(QString uuid, QString pseudo, QString controller, QString vehicle, QString team)
{
    QJsonObject messageJsonObject ;
    messageJsonObject.insert("uuid" , uuid);
    messageJsonObject.insert("pseudo" , pseudo);
    messageJsonObject.insert("controller" , controller);
    messageJsonObject.insert("vehicle" , vehicle);
    messageJsonObject.insert("team" , team == "No team" ? "null" : team);
    QJsonDocument doc(messageJsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    this->publish("/player/register" , strJson);
}

void MqttService::sendMessageControl(QString uuid, int angle, int power, int keyAction)
{
    QJsonObject messageJsonObject ;
    messageJsonObject.insert("uuid" , uuid);
    messageJsonObject.insert("angle" , angle);
    messageJsonObject.insert("power" , power);
    QJsonObject messageJsonButtonsObject ;
    messageJsonButtonsObject.insert("banana" , keyAction == 1 ? true : false);
    messageJsonButtonsObject.insert("bomb" , keyAction == 2 ? true : false);
    messageJsonButtonsObject.insert("rocket" , keyAction == 3 ? true : false);
    messageJsonObject.insert("buttons" , messageJsonButtonsObject);
    QJsonDocument doc(messageJsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    this->publish("/player/control" , strJson);
}

void MqttService::publish(QString pTopic, QString pData)
{
    QMqttTopicName topic(pTopic);
    QByteArray data = pData.toUtf8();
    this->client->publish(topic, data);
}

/**
 * SLot of state mqttCLient
 */
void MqttService::stateChange() {

    switch (client->state()) {
    case 0 :
        qDebug() << "Déconnecté";
        break;
    case 1 :
        qDebug() << "En cours de connexion";
        break;
    case 2 :
        qDebug() << "Connecté";

        subscribes->append(client->subscribe(QString("/player/control")));
        subscribes->append(client->subscribe(QString("/map")));
        subscribes->append(client->subscribe(QString("/")));

        break;
    }
}


/**
 * callback of message receive
 * @param message
 * @param topic
 */
void MqttService::receivedMessage(const QByteArray &message, const QMqttTopicName &topic) {
    qDebug() << message << topic;

    QJsonDocument doc = QJsonDocument::fromJson(message);
    QJsonObject jsonObject = doc.object();

    if (topic == QString("map")) {
        //
        //field->deserialize(jsonObject);

        //qDebug() << field->serialize();

    } else if (topic == QString("game")) {

        emit gameUpdated(jsonObject["color"].toString());

    }else if(topic == QString("/player/control")){
        Map *dataPlayer= Map::instance();
        dataPlayer->deserialize(jsonObject);
        qDebug() << dataPlayer->serialize();


    }
}



