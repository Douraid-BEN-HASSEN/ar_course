#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QKeyEvent>
#include <QGamepad>
#include <Mqtt/MqttService.h>
#include <Kart/Game/Properties.h>
#include "Kart/Player/GameMode.h"


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
    QString getUuid() ;
    int getNbBananas() ;
    int getNbBombs() ;
    int getNbRocket();
    float getAngle() ;
    int getNbTurn() ;
    int getNbTeams() ;
    int getPower() ;
    QGamepad * getGamepad();

    //Setters
    void setUuid(QString uuid);
    void setNbBananas(int n);
    void setNbBombs(int n);
    void setNbRocket(int n);

    QMap<QString, Vehicle *> *getVehicleOptions() const;

private:
    Properties* _properties;
    QString  uuid ;
    int nbTurn ;
    int nbTeam ;
    int power ;
    float  angle ;
    int nbBananas ;
    int nbBomb ;
    int nbRocket ;
    QString controllerType ;
    Properties* getProperties();
    QGamepad *gamepad ;
    QMap<QString , Vehicle *>*vehicleOptions ;

signals:
    void runFind() ;
    void gamemodeFind() ;

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

    //Callback for the player ui
    void setControllerType(QString controllerType);
    void onRunFind() ;
    void onGamemodeFind();
};

#endif // CONTROLLER_H
