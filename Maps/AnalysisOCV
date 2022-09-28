QT -= gui
QT += mqtt

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../../Tools/MqttExchanger/src/Kart/Map/Checkpoint.cpp \
        ../../Tools/MqttExchanger/src/Kart/Map/Field.cpp \
        ../../Tools/MqttExchanger/src/Kart/Map/Obstacle.cpp \
        FieldAruco.cpp \
        MqttService.cpp \
        caruco.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /usr/local/include/opencv4
LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect -lopencv_imgcodecs -lopencv_videoio -lopencv_aruco

HEADERS += \
    ../../Tools/MqttExchanger/src/Kart/Map/Checkpoint.h \
    ../../Tools/MqttExchanger/src/Kart/Map/Field.h \
    ../../Tools/MqttExchanger/src/Kart/Map/Obstacle.h \
    FieldAruco.h \
    MqttService.h \
    caruco.h
