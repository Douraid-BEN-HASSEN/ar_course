QT += core gamepad
QT += mqtt
QT -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Tools/MqttExchanger/src/Kart/Map/Checkpoint.cpp \
    ../Tools/MqttExchanger/src/Kart/Map/Field.cpp \
    ../Tools/MqttExchanger/src/Kart/Map/Obstacle.cpp \
    ../Tools/MqttExchanger/src/Kart/Player/GameMode.cpp \
    ../Tools/MqttExchanger/src/Kart/Player/Item.cpp \
    ../Tools/MqttExchanger/src/Kart/Player/Player.cpp \
    main.cpp \
    mqttservice.cpp

HEADERS += \
    ../Tools/MqttExchanger/src/Kart/Map/Checkpoint.h \
    ../Tools/MqttExchanger/src/Kart/Map/Field.h \
    ../Tools/MqttExchanger/src/Kart/Map/Obstacle.h \
    ../Tools/MqttExchanger/src/Kart/Player/GameMode.h \
    ../Tools/MqttExchanger/src/Kart/Player/Item.h \
    ../Tools/MqttExchanger/src/Kart/Player/Player.h \
    mqttservice.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
