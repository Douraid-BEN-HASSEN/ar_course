#ifndef FIELD_H
#define FIELD_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include "Obstacle.h"
#include "Checkpoint.h"

#include <QList>
#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

//  +------------+
//  | Classe Map |
//  +------------+
class Field : public QObject
{
    Q_OBJECT
public:
    static Field *instance();

    // === UTILS ===
    void deserialize(const QJsonObject &);
    // méthode pour transformer l'objet en QString
    QString serialize();

    QJsonObject toJson();

    // === SETTER ===
    // méthode pour instancier des valeurs depuis une image
    bool setMapInfo(cv::Mat& pImage);

    void setMapWidth(float pMapWidth);
    void setMapHeight(float pMapHeight);

    // méthode pour ajouter un checkpoint
    void addCheckpoint(Checkpoint *pCheckpoint);
    // méthode pour ajouter un obstacle
    void addObstacle(Obstacle *pObstacle);

    // === GETTER ===
    float getMapWidth();
    float getMapHeight();

private:
    // constructor
    explicit Field(QObject *parent = nullptr);
    // destructor
    ~Field();

    float _mapWidth;
    float _mapHeight;

    QMap<int, Checkpoint*> *_checkpoints;
    QMap<int, Obstacle*> *_obstacles;

private slots:

signals:



};

#endif // FIELD_H
