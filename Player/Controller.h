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
    void handleKeyEvent( QKeyEvent *key);
    void handleReleaseKeyEvent(QKeyEvent *key) ;
    void catchKeyUp();
    void catchKeyDown();
    void catchKeyLeft();
    void catchKeyRight();
    void catchKeyAction( int idKey );
    void createGamepad() ;

    //Getters and setter
    QGamepad * getGamepad();
private:
    Properties* _properties;
    QString * uuid ;
    int *power ;
    float * angle ;
    int *nbBananas ;
    int *nbBomb ;
    int *nbRocket ;
    QString controllerType ;
    Properties* getProperties();
    QGamepad *gamepad ;

public slots:
    //Callbacks for gamepad
    void handlePressTurnLeft(bool isPushed) ;
    void handlePressTurnRight(bool isPushed);
    void handlePressBreake(double value) ;
    void handlePressAccelerate (double value);
    void handlePressAction1 (bool isPushed) ;
    void handlePressAction2 (bool isPushed) ;
    void handlePressAction3 (bool isPushed) ;
    void handlePressAction4 (bool isPushed) ;
    void handleTurnLeftJoystick (double value);
    //void handleChangeJoystickLeft();

    void setControllerType(QString controllerType);

};

#endif // CONTROLLER_H
