#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QKeyEvent>
#include <QGamepad>
#include <Mqtt/MqttService.h>
#include <Kart/Game/Properties.h>


class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr );
    Controller(QString *uuid , int *power , float *angle , int *nbBananas , int *nbBomb , int *nbRocket);
    void sendMessageRegister(QString uuid, QString pseudo, QString controller, QString vehicle, QString team);
    void sendMessageControl(QString uuid, int angle, int power, int keyAction);
    Properties* getProperties();
    QGamepad *gamepad ;
    void handleKeyEvent(QString uuid , QKeyEvent *key,  int *power , float *angle , int *nbBananas , int *nbBomb , int *nbRocket);
    void handleReleaseKeyEvent(QKeyEvent *key) ;
    void catchKeyUp(int *power);
    void catchKeyDown(int *power);
    void catwchKeyLeft(float *angle);
    void catchKeyRight(float *angle);
    void catchKeyAction( int idKey , int *nbBanana , int *nbBomb , int *nbRocket);
    void createGamepad() ;

private:
    Properties* _properties;
    QString * uuid ;
    int *power ;
    float * angle ;
    int *nbBananas ;
    int *nbBomb ;
    int *nbRocket ;

public slots:
    //Callbacks for gamepad
    void handlePressTurnLeft(bool isPushed) ;
    void handlePressTurnRight(bool isPushed);
    void handlePressBrak(double value) ;
    void handlePressAccelerate (double value);
    void handlePressAction1 (bool isPushed) ;
    void handlePressAction2 (bool isPushed) ;
    void handlePressAction3 (bool isPushed) ;
    void handlePressAction4 (bool isPushed) ;


signals:

};

#endif // CONTROLLER_H
