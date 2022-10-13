#ifndef IA_H
#define IA_H

#include <QObject>

#include <Kart/Player/Register.h>
#include <Kart/Player/GameMode.h>

class IA : public QObject
{
    Q_OBJECT
public:
    explicit IA(QObject *parent = nullptr);
    IA(Register*, int , int ,  QObject *parent = nullptr);
    void determinePath();
    void initIA() ;
    void mooveToCheckpoint();
    float normalizeAngleD(float angle);
    Player *getActivePlayer();
    void setRegister(Register *);
    void updateLabel() ;
    QPair<int, int> getPairOffset(QPoint currentCheckpoint , Obstacle * obstacle) ;
private:
    bool takeNextCheckpoint = true ;
    int currentCheckpointId = 0 ;
    int obstacleWidth ;
    int obstacleHeight ;
    int obstacleRadius ;
    int speedSelected ;
    int offsetSelected ;
    Player *player ;
    Register *_register;
    Control *_control;
    QList<QPair<QString , Checkpoint*>> path;

signals:
    //Emit signal to draw the path
    void determinePathDone(QList<QPair<QString , Checkpoint*>> resultPath);
    //Emit signal on change target , to refresh the ihm
    void changeTarget(QPoint newTarget) ;
};

#endif // IA_H

