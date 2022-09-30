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
        case QMqttClient::Disconnected :
            message = "Déconnecté";
            break;
        case QMqttClient::Connecting :
            message = "En cours de connexion";
            break;
        case QMqttClient::Connected :
            message = "Connecté";

            for (QString topic : *this->subscribesWait) {
                this->subscribe(topic);
            }

            for (QPair<QString, QString> message : *this->messageWait) {
                this->publish(message.first, message.second);
            }

            break;
    }

    qDebug() << message;

}

bool MqttService::subscribe(QString topic) {

    if (client->state() != QMqttClient::Connected) {
        subscribesWait->append(topic);
        return true;
    }

    qDebug() << QString("MqttService : subscribe to topic : %1").arg(topic);

    subscribes->append(client->subscribe(topic));

    return true;
}

void MqttService::publish(QString topic, QString message) {
    if (client->state() != QMqttClient::Connected) {
        messageWait->append(QPair<QString, QString>(topic, message));
    }

    this->client->publish(topic, message.toUtf8());
    qDebug() << "PUBLISH ! " ;
}

/**
 * callback of message receive
 * @param message
 * @param topic
 */
void MqttService::receivedMessage(const QByteArray &message, const QMqttTopicName &topic) {

    QJsonDocument doc = QJsonDocument::fromJson(message);
    QJsonObject jsonObject = doc.object();

    qDebug() << QString("Topic %1 : %2").arg(topic.name(), "message");

    emit this->message(jsonObject, topic.name());
}

