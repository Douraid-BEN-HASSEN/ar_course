#include "cmqtt.h"
#include <QDebug>

CMQtt::CMQtt(QObject *p, QString pHost, int pPort, QString pUser, QString pPassword) : QObject(p)
{
    this->m_client = new QMqttClient();

    QObject::connect(this->m_client, &QMqttClient::stateChanged, this, &CMQtt::updateLogStateChange);

    this->m_client->setHostname(pHost);
    this->m_client->setPort(pPort);
    this->m_client->setUsername(pUser);
    this->m_client->setPassword(pPassword);
    this->m_client->connectToHost();
}

CMQtt::~CMQtt()
{
    delete this->m_client;
    delete this->_subscriber;
}

void CMQtt::subscribe(QString pTopic)
{
    this->_subscriber = m_client->subscribe(QMqttTopicFilter(pTopic), 1);
    QObject::connect(this->_subscriber, SIGNAL(messageReceived(QMqttMessage)), this, SLOT(updateMessage(QMqttMessage)));
}

void CMQtt::publish(QString pTopic, QString pData) {
    QMqttTopicName topic(pTopic);
    QByteArray data = pData.toUtf8();
    this->m_client->publish(topic, data);
}

void CMQtt::updateLogStateChange()
{
    qDebug() << "Etat mqtt : " << m_client->state();
    /*if(m_client->state() == 2)  this->initSub();*/
    if(this->m_client->state() == 0) this->m_client->connectToHost();
}

//reception msg
void CMQtt::updateMessage(QMqttMessage pMsg)
{
    QJsonObject message = QJsonDocument::fromJson(pMsg.payload()).object();
    qDebug() << message;
}
