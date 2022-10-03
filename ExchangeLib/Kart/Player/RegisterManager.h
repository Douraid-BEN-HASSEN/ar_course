#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H

#if defined(REGISTERMANAGER_LIBRARY)
#  define REGISTERMANAGER_EXPORT Q_DECL_EXPORT
#else
#  define REGISTERMANAGER_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>
#include "Register.h"

#include "Mqtt/MqttService.h"

class RegisterManager : public QObject
{
    Q_OBJECT
public:
    static RegisterManager* getInstance();
    explicit RegisterManager(QObject *parent = nullptr);

    const QString topic = "player/register";

    void publish();



public: signals:
    void application(Register *);

private slots:
    void receivedMessage(QJsonObject message, QString topic);

};

#endif // REGISTERMANAGER_H
