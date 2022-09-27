#ifndef CMQTT_H
#define CMQTT_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtMqtt/QMqttClient>
#include <QList>

class CMQtt: public QObject
{
    Q_OBJECT
public:
    // Constructeur
    CMQtt(QObject*, QString pHost, int pPort, QString pUser, QString pPassword);
    // Destructeur
    ~CMQtt();

    void subscribe(QString pTopic);
    void publish(QString pTopic, QString pData);
private:
    // Client mqtt
    QMqttClient *m_client;
    // Subscriber mqtt
    QMqttSubscription *_subscriber;


public slots:
    // gere le status du client
    void updateLogStateChange();
    // reception du message
    void updateMessage(QMqttMessage);

};

#endif // CMQTT_H

