cmake_minimum_required(VERSION 3.5)

project(MqttExchnager VERSION 0.1 LANGUAGES CXX)

set(Qt5_DIR "~/Qt/5.15.2/gcc_64/lib/cmake/Qt5")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Mqtt REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Mqtt REQUIRED)

set(PROJECT_SOURCES
    src/main.cpp
    src/Kart/Game/Properties.cpp src/Kart/Game/Properties.h
    src/Kart/Game/Vehicle.cpp src/Kart/Game/Vehicle.h
    src/Kart/Map/Field.cpp src/Kart/Map/Field.h
    src/Kart/Map/Obstacle.cpp src/Kart/Map/Obstacle.h
    src/Kart/Map/Checkpoint.cpp src/Kart/Map/Checkpoint.h
    src/Kart/Player/Player.cpp src/Kart/Player/Player.h
    src/Mqtt/MqttService.cpp src/Mqtt/MqttService.h
    src/window.cpp src/window.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MqttExchnager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MqttExchnager APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MqttExchnager SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MqttExchnager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MqttExchnager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Mqtt)

set_target_properties(MqttExchnager PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MqttExchnager)
endif()
