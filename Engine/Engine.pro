QT += core gamepad
QT += mqtt
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEPENDPATH += . ../ExchangeLib
INCLUDEPATH += ../ExchangeLib

unix {
    LIBS += -L../ExchangeLib -lExchangeLib
}

win32 {
    LIBS += -L../ExchangeLib/debug -lExchangeLib
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    2DGraphics/CheckpointGraphics.cpp \
    2DGraphics/ObstacleGraphics.cpp \
    2DGraphics/PlayerGraphics.cpp \
    2DGraphics/widget.cpp \
    Engine.cpp \
    GCheckpoint.cpp \
    GEngine.cpp \
    GObstacle.cpp \
    GPlayer.cpp \
    main.cpp

HEADERS += \
    2DGraphics/CheckpointGraphics.h \
    2DGraphics/ObstacleGraphics.h \
    2DGraphics/PlayerGraphics.h \
    2DGraphics/widget.h \
    Engine.h \
    GCheckpoint.h \
    GEngine.h \
    GObstacle.h \
    GPlayer.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    2DGraphics/widget.ui
