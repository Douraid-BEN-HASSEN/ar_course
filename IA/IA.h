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
    IA(Register*, QObject *parent = nullptr);

    void brain();

    Player *getActivePlayer();
    void setRegister(Register *);

    Checkpoint* getNextCheckpoint(int lastCheckpointId);

private:
    Register *_register;
    Control *_control;

signals:

};

#endif // IA_H
