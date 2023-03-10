QT       += core gui
QT += mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Kart/Game/Properties.cpp \
    src/Kart/Game/Vehicle.cpp \
    src/Kart/Map/Field.cpp \
    src/Kart/Map/Obstacle.cpp \
    src/Kart/Map/Checkpoint.cpp \
    src/Kart/Player/Player.cpp \
    src/Mqtt/MqttService.cpp \
    src/main.cpp \
    src/window.cpp

HEADERS += \
    src/Kart/Game/Properties.h \
    src/Kart/Game/Vehicle.h \
    src/Kart/Map/Field.h \
    src/Kart/Map/Obstacle.h \
    src/Kart/Map/Checkpoint.h \
    src/Kart/Player/Player.h \
    src/Mqtt/MqttService.h \
    src/window.h

FORMS += \
    src/window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
