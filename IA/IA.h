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
    void determinerChemin();
    void brain();
    void brain2() ;
    void brain3();
    void initIA() ;
    void mooveToCheckpoint();
    float normalizeAngleD(float angle);
    Player *getActivePlayer();
    void setRegister(Register *);

    Checkpoint* getNextCheckpoint(int lastCheckpointId);
private:
    int currentCheckpointId = 0 ;
    Player *player ;
    Register *_register;
    Control *_control;
    QList<Checkpoint *>  path ;
signals:

};

#endif // IA_H
