#include "MqttService.h"

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

    client->connectToHost();

    subscribes = new QList<QMqttSubscription *>;

    /* -- connect -- */
    connect(client, &QMqttClient::stateChanged, this, &MqttService::stateChange);
    connect(client, &QMqttClient::messageReceived, this, &MqttService::receivedMessage);
}

/**
 * SLot of state mqttCLient
 */
void MqttService::stateChange() {

    QString message;
    switch (client->state()) {
        case 0 :
            message = "Déconnecté";
            break;
        case 1 :
            message = "En cours de connexion";
            break;
        case 2 :
            message = "Connecté";

            subscribes->append(client->subscribe(QString("/map")));
            subscribes->append(client->subscribe(QString("/game")));

            break;
    }

    qDebug() << message;

}

/**
 * callback of message receive
 * @param message
 * @param topic
 */
void MqttService::receivedMessage(const QByteArray &message, const QMqttTopicName &topic) {
    //qDebug() << message << topic;

    QJsonDocument doc = QJsonDocument::fromJson(message);
    QJsonObject jsonObject = doc.object();

    if (topic == QString("/map")) {
        Field *field = Field::instance();
        field->deserialize(jsonObject);

    } else if (topic == QString("game")) {

        emit gameUpdated(jsonObject["color"].toString());
    }
}

