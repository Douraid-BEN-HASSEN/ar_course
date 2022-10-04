QT += 3dcore 3drender 3dinput 3dlogic 3dextras 3danimation core gui mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEPENDPATH += . ../ExchangeLib
INCLUDEPATH += ../ExchangeLib

unix {
    LIBS += -L../ExchangeLib -lExchangeLib
}

win32 {
    LIBS += -L../ExchangeLib/debug -lExchangeLib
}

SOURCES += \
    3DGraphics/Widget3D.cpp \
    3DGraphics/checkpointGraphics3D.cpp \
    3DGraphics/obstacleGraphics3D.cpp \
    3DGraphics/orbittransformcontroller.cpp \
    3DGraphics/playerGraphics3D.cpp \
    main.cpp \

HEADERS += \
    3DGraphics/Widget3D.h \
    3DGraphics/checkpointGraphics3D.h \
    3DGraphics/obstacleGraphics3D.h \
    3DGraphics/orbittransformcontroller.h \
    3DGraphics/playerGraphics3D.h \

FORMS += \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
