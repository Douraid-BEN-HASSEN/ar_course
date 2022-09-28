#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QJsonObject>

class Item : public QObject
{
    Q_OBJECT
public:
    explicit Item(QObject *parent = nullptr);

    void deserialize(const QJsonObject &jsonObject);

    void setX(int pX);
    void setY(int pY);
    void setAngle(float pAngle);
    void setStatus(QString pStatut);

    int getX();
    int getY();
    float getAngle();
    QString getStatus();
    QString getType();

private:
    int _x,_y;
    float _angle;
    QString _status;
    QString _type;

signals:

};

#endif // ITEM_H
