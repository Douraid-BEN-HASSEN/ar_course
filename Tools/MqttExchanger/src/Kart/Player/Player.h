#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMap>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    ~Player();

    // === UTILS ===
    void deserialize(const QJsonObject &);
    QString serialize();
    QJsonObject toJson();

    // === SETTER ===
    void setUuid(QString pUuid);
    void setPseudo(QString pPseudo);
    void setColor(QString pColor);
    void setTeam(QString pTeam);
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
    int getSpeed();
    QString getVehicule();
    QMap<QString, int>* getItems();
    int getLastCheckpoint();
    int getCurrentLap();
    QString getStatus();
    QString getController();

private:
    QString _uuid;
    QString _pseudo;
    QString _color;
    QString _team;
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
