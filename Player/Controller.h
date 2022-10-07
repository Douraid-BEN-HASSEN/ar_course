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
    //Constructor
    explicit Controller(QObject *parent = nullptr );

    //For the keyboard
    void handleKeyEvent( QKeyEvent *key);
    void handleReleaseKeyEvent(QKeyEvent *key) ;
    void catchKeyUp();
    void catchKeyDown();
    void catchKeyLeft();
    void catchKeyRight();
    void catchKeyAction( int idKey );

    //For the gamepad
    void createGamepad() ;

    //For the mqtt
    void sendMessageRegister(QString pseudo, QString controller, QString vehicle, QString team);
    void sendMessageControl( int keyAction);

    //Getters
    int getNbBananas() ;
    int getNbBombs() ;
    int getNbRocket();
    float getAngle() ;
    int getPower() ;
    QGamepad * getGamepad();

    //Setters
    void setNbBananas(int n);
    void setNbBombs(int n);
    void setNbRocket(int n);
private:
    Properties* _properties;
    QString  uuid ;
    int power ;
    float  angle ;
    int nbBananas ;
    int nbBomb ;
    int nbRocket ;
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

    void setControllerType(QString controllerType);

};

#endif // CONTROLLER_H
