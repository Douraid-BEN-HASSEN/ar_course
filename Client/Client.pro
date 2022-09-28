QT       += core gui
QT  += mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Kart/Map/Checkpoint.cpp \
    Kart/Map/Field.cpp \
    Kart/Map/Obstacle.cpp \
    Mqtt/MqttService.cpp \
    Player.cpp \
    main.cpp \
    interface.cpp \
    testQGraphics2022/obstaclerect.cpp \
    testQGraphics2022/widget.cpp

HEADERS += \
    Kart/Map/Checkpoint.h \
    Kart/Map/Field.h \
    Kart/Map/Obstacle.h \
    Mqtt/MqttService.h \
    Player.h \
    interface.h \
    testQGraphics2022/obstaclerect.h \
    testQGraphics2022/widget.h

FORMS += \
    interface.ui \
    testQGraphics2022/widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
