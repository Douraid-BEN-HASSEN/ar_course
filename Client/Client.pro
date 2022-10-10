QT       += core gui
QT  += mqtt

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
    2DGraphics/RocketGraphics.cpp \
    2DGraphics/BombGraphics.cpp \
    2DGraphics/BananaGraphics.cpp \
    2DGraphics/CheckpointGraphics.cpp \
    2DGraphics/ItemGraphics.cpp \
    2DGraphics/ObstacleGraphics.cpp \
    2DGraphics/PlayerGraphics.cpp \
    2DGraphics/widget.cpp \
    interface.cpp \
    main.cpp

HEADERS += \
    2DGraphics/RocketGraphics.h \
    2DGraphics/BombGraphics.h \
    2DGraphics/BananaGraphics.h \
    2DGraphics/CheckpointGraphics.h \
    2DGraphics/ItemGraphics.h \
    2DGraphics/ObstacleGraphics.h \
    2DGraphics/PlayerGraphics.h \
    2DGraphics/widget.h \
    interface.h

FORMS += \
    interface.ui \
    2DGraphics/widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
