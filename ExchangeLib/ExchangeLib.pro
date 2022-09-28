QT -= gui
QT += mqtt

TEMPLATE = lib

CONFIG += c++17

DEFINES += \
    MQTTSERVICE_LIBRARY \
    MAP_LIBRARY \
    CHECKPOINT_LIBRARY \
    OBSTACLE_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Kart/Map/Checkpoint.cpp \
    Kart/Map/Map.cpp \
    Kart/Map/Obstacle.cpp \
    Mqtt/MqttService.cpp

HEADERS += \
    Kart/Map/Checkpoint.h \
    Kart/Map/Map.h \
    Kart/Map/Obstacle.h \
    Mqtt/MqttService.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
