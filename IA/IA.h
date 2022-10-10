#ifndef IA_H
#define IA_H

#include <QObject>

#include <Kart/Player/Register.h>
#include <Kart/Player/GameMode.h>

class IA : public QObject
{
    Q_OBJECT
public:;
    explicit IA(QObject *parent = nullptr);
    IA(Register*, QObject *parent = nullptr);
    void determinePath();
    void initIA() ;
    void mooveToCheckpoint();
    float normalizeAngleD(float angle);
    Player *getActivePlayer();
    void setRegister(Register *);

private:
    int currentCheckpointId = 0 ;
    int obstacleWidth ;
    int obstacleHeight ;
    int obstacleRadius ;
    Player *player ;
    Register *_register;
    Control *_control;
    QList<Checkpoint *>  path;
    QList<QPair<QString , Checkpoint*>> path2;

signals:
    void determinePathDone(QList<QPair<QString , Checkpoint*>> resultPath);

};

#endif // IA_H
