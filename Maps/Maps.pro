QT -= gui
QT += mqtt

CONFIG += c++17
CONFIG -= app_bundle

DEPENDPATH += . ../ExchangeLib
INCLUDEPATH += ../ExchangeLib

unix {
    INCLUDEPATH += /usr/local/include/opencv4

    LIBS += -L../ExchangeLib -lExchangeLib
    LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect -lopencv_imgcodecs -lopencv_videoio -lopencv_aruco

}

win32 {
    # todo implmente opencv4 for windows
    LIBS += -L../ExchangeLib/debug -lExchangeLib
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        FieldAruco.cpp \
        main.cpp

HEADERS += \
    FieldAruco.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



