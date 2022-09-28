#ifndef CPLAYER_H
#define CPLAYER_H

#include "mqttservice.h"

class CPlayer
{
public:
    CPlayer();
private:
    MqttService *_mqtt = MqttService::instance();

};

#endif // CPLAYER_H
