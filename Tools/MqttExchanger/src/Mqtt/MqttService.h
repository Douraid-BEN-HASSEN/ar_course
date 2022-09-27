#ifndef MQTTSERVICE_H
#define MQTTSERVICE_H

#include <QObject>
#include <QtMqtt/QtMqtt>
#include <QJsonDocument>
#include <QJsonObject>
#include "src/Kart/Map/Field.h"

const static struct {
    const QString hostname = "localhost";
    const unsigned short port = 1883;
    const QString username = "user";
    const QString password = "pass";
} Config;

class MqttService: public QObject
{
    Q_OBJECT
public:
    static MqttService *instance();

    QMqttClient *client;


private:
    explicit MqttService(QObject * parent = nullptr);

    QList<QMqttSubscription *> *subscribes;

private slots:
    void stateChange();
    void receivedMessage(const QByteArray &message, const QMqttTopicName &topic);

public: signals:
    void mapUpdated(QJsonObject jsonObject);
    void gameUpdated(QString color);

};
#endif // MQTTSERVICE_H


