#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

#include <Mqtt/MqttService.h>
#include <Kart/Game/Properties.h>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    void sendMessageRegister(QString uuid, QString pseudo, QString controller, QString vehicle, QString team);
    void sendMessageControl(QString uuid, int angle, int power, int keyAction);

    Properties* getProperties();

private:
    Properties* _properties;

signals:

};

#endif // CONTROLLER_H
