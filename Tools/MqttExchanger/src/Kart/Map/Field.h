#ifndef FIELD_H
#define FIELD_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>

#include "Obstacle.h"
#include "Checkpoint.h"

class Field : public QObject
{
    Q_OBJECT
public:
    static Field *instance();

    float width;
    float height;

    QMap<int, Obstacle*> *obstacles = new QMap<int, Obstacle*>();
    QMap<int, Checkpoint*> *checkpoints = new QMap<int, Checkpoint*>();

    void deserialize(const QJsonObject &);
    QString serialize();
    QJsonObject toJson();


private:
    explicit Field(QObject *parent = nullptr);

private slots:

signals:



};

#endif // FIELD_H
