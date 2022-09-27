#ifndef MQTTSERVICE_H
#define MQTTSERVICE_H

#include <QObject>
#include <QtMqtt/QtMqtt>
#include <QJsonDocument>
#include <QJsonObject>

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
    
private slots:
    void stateChange();
    void receivedMessage(const QByteArray &message, const QMqttTopicName &topic);

public: signals:
    void mapUpdated(QJsonObject jsonObject);
    void gameUpdated(QString color);

};
#endif // MQTTSERVICE_H


