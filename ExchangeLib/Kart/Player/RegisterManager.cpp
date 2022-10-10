#include "RegisterManager.h"

RegisterManager *RegisterManager::getInstance() {
    static RegisterManager *instance;

    if (instance == nullptr) {
        qDebug() << "new instance Map";
        instance = new RegisterManager();

        MqttService::instance()->subscribe(instance->topic);

        /* -- connect -- */
        /* todo implmente an interface and methode to connect */
        connect(MqttService::instance(), &MqttService::message, instance, &RegisterManager::receivedMessage);

        qDebug() << "Map connected";
    }

    return instance;
}


RegisterManager::RegisterManager(QObject *parent): QObject{parent}
{

}

void RegisterManager::receivedMessage(QJsonObject message, QString topic) {
    if (topic == RegisterManager::topic) {
        qDebug() << "register recive";
        Register *r = new Register;
        r->deserialize(message);

        emit application(r);
    }
}
