cmake_minimum_required(VERSION 3.14)

project(MotionAuthApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Quick Sensors REQUIRED)

qt_add_executable(MotionAuthApp
    main.cpp
    kalmanfilter.h
    kalmanfilter.cpp
    sensordatahandler.h
    sensordatahandler.cpp
)

qt_add_qml_module(MotionAuthApp
    URI MotionAuthApp
    VERSION 1.0
    QML_FILES main.qml
)

target_link_libraries(MotionAuthApp
    Qt6::Core
    Qt6::Quick
    Qt6::Sensors
)

install(TARGETS MotionAuthApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
