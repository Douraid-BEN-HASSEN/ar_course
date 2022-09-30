#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QKeyEvent>

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
    void handleKeyEvent(QString uuid , QKeyEvent *key,  int *power , float *angle , int *nbBananas , int *nbBomb , int *nbRocket);
    void catchKeyUp(int *power);
    void catchKeyDown(int *power);
    void catchKeyLeft(float *angle);
    void catchKeyRight(float *angle);
    void catchKeyAction( int idKey , int *nbBanana , int *nbBomb , int *nbRocket);
private:
    Properties* _properties;

signals:

};

#endif // CONTROLLER_H