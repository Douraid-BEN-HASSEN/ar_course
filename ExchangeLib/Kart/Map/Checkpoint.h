#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

/**
 * @brief The Checkpoint class
 */
class Checkpoint : public QObject
{
    Q_OBJECT
public:
    // constructor
    explicit Checkpoint(QObject *parent = nullptr);
    // desctructor
    ~Checkpoint();

    // === UTILS ===
    void deserialize(const QJsonObject &json);
    QString serialize();
    QJsonObject toJson();

    // === SETTER ===
    void setId(int pId);
    void setX(int pX);
    void setY(int pY);
    void setTimeout(int pTimeout);

    // === GETTER ===
    int getId();
    int getX();
    int getY();
    int getTimeout();

private:
    int _id;
    int _x;
    int _y;
    int _timeout;

signals:

};

#endif // CHECKPOINT_H
