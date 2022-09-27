#include "MqttService.h"

MqttService *MqttService::instance()
{
    static MqttService instance;
    return &instance;
}

void MqttService::publish(QString pTopic, QString pData)
{
    QMqttTopicName topic(pTopic);
    QByteArray data = pData.toUtf8();
    this->client->publish(topic, data);
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

            subscribes->append(client->subscribe(QString("map")));
            subscribes->append(client->subscribe(QString("game")));

            break;
    }

}

/**
 * callback of message receive
 * @param message
 * @param topic
 */
void MqttService::receivedMessage(const QByteArray &message, const QMqttTopicName &topic) {
    /*qDebug() << message << topic;

    QJsonDocument doc = QJsonDocument::fromJson(message);
    QJsonObject jsonObject = doc.object();

    if (topic == QString("map")) {
        Field *field = Field::instance();
        field->deserialize(jsonObject);

        qDebug() << field->serialize();

    } else if (topic == QString("game")) {

        emit gameUpdated(jsonObject["color"].toString());

    }*/
}

