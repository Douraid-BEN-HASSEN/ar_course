QT       += core gui
QT += 3dcore 3drender 3dinput 3dlogic 3dextras 3danimation core gui mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEPENDPATH += . ../ExchangeLib
INCLUDEPATH += ../ExchangeLib ../Player

unix {
    LIBS += -L../ExchangeLib -lExchangeLib
}

win32 {
    LIBS += -L../ExchangeLib/debug -lExchangeLib
}

SOURCES += \
    main.cpp \
    client3dplayer.cpp \
    ../Player/playerui.cpp \
    ../Player/Controller.cpp \
    ../Client3D/3DGraphics/Widget3D.cpp \
    ../Client3D/3DGraphics/bananaGraphics3D.cpp  \
    ../Client3D/3DGraphics/bombGraphics3D.cpp  \
    ../Client3D/3DGraphics/checkpointGraphics3D.cpp \
    ../Client3D/3DGraphics/gone.cpp \
    ../Client3D/3DGraphics/obstacleGraphics3D.cpp \
    ../Client3D/3DGraphics/planeGraphics3D.cpp \
    ../Client3D/3DGraphics/playerGraphics3D.cpp \
    ../Client3D/3DGraphics/roadgraphics3d.cpp \
    ../Client3D/3DGraphics/rocketGraphics3D.cpp \

HEADERS += \
    client3dplayer.h \
    ../Player/playerui.h \
    ../Player/Controller.h \
    ../Client3D/3DGraphics/Widget3D.h \
    ../Client3D/3DGraphics/bananaGraphics3D.h  \
    ../Client3D/3DGraphics/bombGraphics3D.h  \
    ../Client3D/3DGraphics/checkpointGraphics3D.h \
    ../Client3D/3DGraphics/gone.h \
    ../Client3D/3DGraphics/obstacleGraphics3D.h\
    ../Client3D/3DGraphics/planeGraphics3D.h\
    ../Client3D/3DGraphics/playerGraphics3D.h\
    ../Client3D/3DGraphics/roadgraphics3d.h\
    ../Client3D/3DGraphics/rocketGraphics3D.h\

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
