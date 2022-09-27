#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QObject>
#include <QJsonObject>

class Checkpoint : public QObject
{
    Q_OBJECT
public:
    explicit Checkpoint(QObject *parent = nullptr);

    int id;
    int x;
    int y;

    void deserialize(const QJsonObject &);
    QString serialize();
    QJsonObject toJson();

signals:

};

#endif // CHECKPOINT_H
