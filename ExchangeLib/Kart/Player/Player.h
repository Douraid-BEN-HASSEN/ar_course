#ifndef PLAYER_H
#define PLAYER_H

#if defined(PLAYER_LIBRARY)
#  define PLAYER_EXPORT Q_DECL_EXPORT
#else
#  define PLAYER_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>
#include <QMap>
#include "Kart/Game/Control.h"
#include "Kart/Map/Map.h"

class PLAYER_EXPORT Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    ~Player();

    // === UTILS ===
    QString toString();

    void deserialize(const QJsonObject &);
    QString serialize();
    QJsonObject toJson();


    // === SETTER ===
    void setUuid(QString pUuid);
    void setPseudo(QString pPseudo);
    void setColor(QString pColor);
    void setTeam(QString pTeam);
    void setX(int pX);
    void setY(int pY);
    void setAngle(float pAngle);
    void setSpeed(int pSpeed);
    void setVehicule(QString pVehicule);
    void setLastCheckpoint(int pLastCheckpoint);
    void setCurrentLap(int pCurrentLap);
    void setStatus(QString pStatus);
    void setController(QString pController);

    // === GETTER ===
    QString getUuid();
    QString getPseudo();
    QString getColor();
    QString getTeam();
    int getX();
    int getY();
    float getAngle();
    int getSpeed();
    QString getVehicule();
    QMap<QString, int>* getItems();
    int getLastCheckpoint();
    int getCurrentLap();
    QString getStatus();
    QString getController();

    void update(Control *control);

private:
    Map *_map;
    QString _uuid;
    QString _pseudo;
    QString _color;
    QString _team;
    int _x;
    int _y;
    float _angle;
    int _speed;
    QString _vehicle; // enum a modifier
    QMap<QString, int> *_items;
    int _lastCheckpoint;
    int _currentLap;
    QString _status;
    QString _controller;

signals:

};

#endif // PLAYER_H
