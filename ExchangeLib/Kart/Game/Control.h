#ifndef CONTROL_H
#define CONTROL_H

#if defined(CONTROL_LIBRARY)
#  define CONTROL_EXPORT Q_DECL_EXPORT
#else
#  define CONTROL_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>

#include <QString>
#include <QMap>
#include <QJsonObject>
#include <QJsonDocument>

#include <Mqtt/MqttService.h>

class CONTROL_EXPORT Control: public QObject
{
    Q_OBJECT
public:
    Control(QObject *parent = nullptr);
    Control(QString uuid, QObject *parent = nullptr);

    const QString topic = "player/control";

    void publish();

    QString toString();
    void deserialize(const QJsonObject &);
    QString serialize();
    QJsonObject toJson();

    void setUuid(QString pUuid);
    void setAngle(float pAngle);
    void setPower(int pPower);
    void setButtonsVal(QString pKey, bool pVal);
    void setButtons(QMap<QString, bool> pButtons);

    QString getUuid();
    float getAngle();
    int getPower();
    bool getButtonsVal(QString pKey);
    QMap<QString, bool> getButtons();

private:
    QString _uuid = "";
    float _angle = 0.f;
    int _power = 0;
    QMap<QString, bool> _buttons;

};

#endif // CONTROL_H
