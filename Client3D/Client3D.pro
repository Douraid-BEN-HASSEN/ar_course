QT += 3dcore 3drender 3dinput 3dlogic 3dextras qml quick 3dquick 3danimation core gui mqtt

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
    checkpointgraphics.cpp \
    interface.cpp \
    main.cpp \
    obstaclegraphics.cpp \
    orbittransformcontroller.cpp \
    playergraphics.cpp \
    widget.cpp

HEADERS += \
    checkpointgraphics.h \
    interface.h \
    obstaclegraphics.h \
    orbittransformcontroller.h \
    playergraphics.h \
    widget.h

FORMS += \
    interface.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
