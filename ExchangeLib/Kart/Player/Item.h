#ifndef ITEM_H
#define ITEM_H

#if defined(ITEM_LIBRARY)
#  define ITEM_EXPORT Q_DECL_EXPORT
#else
#  define ITEM_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

class ITEM_EXPORT Item : public QObject
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
