#ifndef MQTTSERVICE_H
#define MQTTSERVICE_H

#if defined(MQTTSERVICE_LIBRARY)
#  define MQTTSERVICE_EXPORT Q_DECL_EXPORT
#else
#  define MQTTSERVICE_EXPORT Q_DECL_IMPORT
#endif

#include <QtCore/qglobal.h>
#include <QObject>
#include <QtMqtt/QtMqtt>
#include <QJsonDocument>
#include <QJsonObject>

const static struct {
    const QString hostname = "localhost";
    const unsigned short port = 1883;
    const QString username = "user";
    const QString password = "pass";
} Config;

/**
 * @brief The MqttService class
 */
class MQTTSERVICE_EXPORT MqttService: public QObject
{
    Q_OBJECT
public:
    static MqttService *instance();
    QMqttClient *client;
    bool subscribe(QString topic);


private:
    explicit MqttService(QObject * parent = nullptr);
    QList<QMqttSubscription *> *subscribes;

private slots:
    void stateChange();
    void receivedMessage(const QByteArray &message, const QMqttTopicName &topic);

public: signals:
    void message(QJsonObject jsonObject, QString topic);

};
#endif // MQTTSERVICE_H


