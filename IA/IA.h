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
    IA(Register*, int ,  QObject *parent = nullptr);
    void determinePath();
    void initIA() ;
    void mooveToCheckpoint();
    float normalizeAngleD(float angle);
    Player *getActivePlayer();
    void setRegister(Register *);
    void updateLabel() ;
private:
    bool takeNextCheckpoint = true ;
    int currentCheckpointId = 0 ;
    int obstacleWidth ;
    int obstacleHeight ;
    int obstacleRadius ;
    int speedSelected ;
    Player *player ;
    Register *_register;
    Control *_control;
    QList<QPair<QString , Checkpoint*>> path;

signals:
    void determinePathDone(QList<QPair<QString , Checkpoint*>> resultPath);

};

#endif // IA_H
