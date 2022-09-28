#ifndef MQTTSERVICE_H
#define MQTTSERVICE_H

#include <QObject>
#include <QtMqtt/QtMqtt>
#include <QJsonDocument>
#include <QJsonObject>
#include "../Tools/MqttExchanger/src/Kart/Player/GameMode.h"

const static struct {
    const QString hostname = "127.0.0.1";
    const unsigned short port = 1883;
    const QString username = "";
    const QString password = "";
} Config;

class MqttService: public QObject
{
    Q_OBJECT
public:
    static MqttService *instance();

    QMqttClient *client;
    // méthode pour publier
    void publish(QString pTopic, QString pData);

private:
    explicit MqttService(QObject * parent = nullptr);
    QList<QMqttSubscription *> *subscribes;
    GameMode _gameMode;

public :
    void sendMessageRegister(QString uuid , QString pseudo , QString controller, QString vehicle, QString team);
    void sendMessageControl(QString uuid , int angle , int power , int keyAction);

private slots:
    void stateChange();
    void receivedMessage(const QByteArray &message, const QMqttTopicName &topic);

signals:
    void message(QJsonObject pMessage, QString pTopic);
};


#endif // MQTTSERVICE_H

