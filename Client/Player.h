#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    QString uuid;
    QString pseudo;
    QString color;
    QString team;
    int speed;
    QString vehicle; // enum a modifier
    QMap<QString, int> *items = new QMap<QString, int>();
    int lastCheckpoint;
    int currentLap;
    QString status;
    QString controller;



    void deserialize(const QJsonObject &json);
signals:

signals:

};

#endif // PLAYER_H
