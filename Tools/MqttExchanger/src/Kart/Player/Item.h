#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

class Item : public QObject
{
    Q_OBJECT
public:
    explicit Item(QObject *parent = nullptr);

    // === UTILS ===
    void deserialize(const QJsonObject &jsonObject);
    QString serialize();
    QJsonObject toJson();

    // === SETTER ===
    void setX(int pX);
    void setY(int pY);
    void setAngle(float pAngle);
    void setStatus(QString pStatut);

    // === GETTER ===
    int getX();
    int getY();
    float getAngle();
    QString getStatus();
    QString getType();

private:
    int _x;
    int _y;
    float _angle;
    QString _status;
    QString _type;

signals:

};

#endif // ITEM_H
