cmake_minimum_required(VERSION 3.5)

project(ExchangeLib LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Mqtt)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Mqtt )

add_library(ExchangeLib SHARED
        Kart/Map/Map.cpp Kart/Map/Map.h
        Kart/Map/Checkpoint.cpp Kart/Map/Checkpoint.h
        Kart/Map/Obstacle.cpp Kart/Map/Obstacle.h

        Kart/Game/Properties.cpp Kart/Game/Properties.h
        Kart/Game/Vehicle.cpp Kart/Game/Vehicle.h

        Kart/Player/GameMode.cpp Kart/Player/GameMode.h
        Kart/Player/Item.cpp Kart/Player/Item.h
        Kart/Player/Player.cpp Kart/Player/Player.h
        )

target_link_libraries(ExchangeLib PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_compile_definitions(ExchangeLib PRIVATE EXCHANGELIB_LIBRARY)
