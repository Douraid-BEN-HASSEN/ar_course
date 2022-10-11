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
    explicit Item(QPoint, QString type, QObject *parent = nullptr);
    explicit Item(int x, int y, QString type, QObject *parent = nullptr);

    // === UTILS ===
    void deserialize(const QJsonObject &jsonObject);
    QString serialize();
    QJsonObject toJson();

    // === SETTER ===
    void setPos(const QPoint &pos);
    inline void setPos(int x, int y);

    QString getUuid();

    int getX();
    void setX(int pX);

    void setY(int pY);
    int getY();

    void setAngle(float pAngle);
    float getAngle();

    void setStatus(QString pStatut);
    QString getStatus();

    // === GETTER ===
    QString getType();

private:
    QString _uuid;
    int _x;
    int _y;
    float _angle;
    QString _status;
    QString _type;

signals:

};

#endif // ITEM_H
