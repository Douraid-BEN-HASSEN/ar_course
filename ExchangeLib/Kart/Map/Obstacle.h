#ifndef OBSTACLE_H
#define OBSTACLE_H

#if defined(OBSTACLE_LIBRARY)
#  define OBSTACLE_EXPORT Q_DECL_EXPORT
#else
#  define OBSTACLE_EXPORT Q_DECL_IMPORT
#endif


#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

/**
 * @brief The Obstacle class
 */
class OBSTACLE_EXPORT Obstacle : public QObject
{
    Q_OBJECT
public:
    // constructor
    explicit Obstacle(QObject *parent = nullptr);
    // destructor
    ~Obstacle();

    // === UTILS ===
    void deserialize(const QJsonObject &json);
    QString serialize();
    QJsonObject toJson();

    // === SETTER ===
    void setId(int pId);
    void setX(int pX);
    void setY(int pY);
    void setAngle(float pAngle);
    void setTimeout(int pTimeout);

    // === GETTER ===
    int getId();
    int getX();
    int getY();
    float getAngle();
    int getTimeout();

private:
    int _id;
    int _x;
    int _y;
    float _angle;
    int _timeout;

signals:

};

#endif // OBSTACLE_H
