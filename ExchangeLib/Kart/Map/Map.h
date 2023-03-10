#ifndef MAP_H
#define MAP_H

#if defined(MAP_LIBRARY)
#  define MAP_EXPORT Q_DECL_EXPORT
#else
#  define MAP_EXPORT Q_DECL_IMPORT
#endif


#include <QObject>
#include <QMap>
#include <QList>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <QDebug>

#include "Obstacle.h"
#include "Checkpoint.h"
#include "Mqtt/MqttService.h"

/**
 * @brief The Map class
 */
class MAP_EXPORT Map : public QObject
{
    Q_OBJECT
public:
    static Map *getInstance();

    // constructor
    explicit Map(QObject *parent = nullptr);

    const QString topic = "map";

    // === UTILS ===
    void deserialize(const QJsonObject &);

    // méthode pour transformer l'objet en QString
    QString serialize();
    QJsonObject toJson();

    void publish();

    // === SETTER ===
    void setMapWidth(float pMapWidth);
    void setMapHeight(float pMapHeight);

    // méthode pour ajouter un checkpoint
    void addCheckpoint(Checkpoint *pCheckpoint);
    // méthode pour ajouter un obstacle
    void addObstacle(Obstacle *pObstacle);
    //méthode pour ajouter une ligne
    void addLine(QLineF *pLine);

    // === GETTER ===
    float getMapWidth();
    float getMapHeight();
    QMap<int, Checkpoint *>* getCheckpoints();
    QMap<int, Obstacle*>* getObstacles();

    void reste();
private:

    float _mapWidth;
    float _mapHeight;

protected:
    // destructor
    ~Map();

    QMap<int, Checkpoint*> *_checkpoints;
    QMap<int, Obstacle*> *_obstacles;
    QMap<int, QLineF*> *_lines ;

private slots:
    void receivedMessage(QJsonObject message, QString topic);

public: signals:
    void updated();

};
#endif // MAP_H
