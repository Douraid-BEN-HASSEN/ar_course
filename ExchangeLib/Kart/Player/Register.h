#ifndef REGISTER_H
#define REGISTER_H

#if defined(REGISTER_LIBRARY)
#  define REGISTER_EXPORT Q_DECL_EXPORT
#else
#  define REGISTER_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>

#include <QJsonObject>
#include <QJsonDocument>

#include <Mqtt/MqttService.h>

class REGISTER_EXPORT Register : public QObject
{
    Q_OBJECT
public:
    explicit Register(QObject *parent = nullptr);
    Register(QString pseudo, QString controller, QString vehicle, int team, QObject *parent = nullptr);

    const QString topic = "player/register";

    void publish();

    // === UTILS ===
    QString toString();

    void deserialize(const QJsonObject &);
    QString serialize();
    QJsonObject toJson();

    QString getUuid();
    QString getPseudo();
    QString getController();
    QString getVehicle();
    int getTeam();

private:
    QString _uuid = "";
    QString _pseudo = "";
    QString _controller = "";
    QString _vehicle = "";
    int _team = 0;

signals:

};

#endif // REGISTER_H
