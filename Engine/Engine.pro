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
    2DGraphics/GBanana.cpp \
    2DGraphics/GBomb.cpp \
    2DGraphics/GCheckpoint.cpp \
    2DGraphics/GEngine.cpp \
    2DGraphics/GItem.cpp \
    2DGraphics/GObstacle.cpp \
    2DGraphics/GPlayer.cpp \
    2DGraphics/GRocket.cpp \
    Engine.cpp \
    main.cpp \
    window.cpp

HEADERS += \
    2DGraphics/GBanana.h \
    2DGraphics/GBomb.h \
    2DGraphics/GCheckpoint.h \
    2DGraphics/GEngine.h \
    2DGraphics/GItem.h \
    2DGraphics/GObstacle.h \
    2DGraphics/GPlayer.h \
    2DGraphics/GRocket.h \
    Engine.h \
    window.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    window.ui

