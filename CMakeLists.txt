cmake_minimum_required(VERSION 3.16)

project(MotionBasedAuthentication VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

find_package(Qt6 COMPONENTS Sensors REQUIRED)


qt_standard_project_setup()

qt_add_executable(appMotionBasedAuthentication
    main.cpp
    kalmanfilter.h
    kalmanfilter.cpp
    sensordatahandler.h
    sensordatahandler.cpp
)

qt_add_qml_module(appMotionBasedAuthentication
    URI MotionBasedAuthentication
    NO_RESOURCE_TARGET_PATH
    VERSION 1.0
    QML_FILES
    Main.qml
    #SOURCES sensorFilter.h
    #SOURCES sensorFilter.cpp
    #SOURCES sensorManager.h
    #SOURCES sensorManager.cpp
    #SOURCES motionPattern.h
    #SOURCES motionPattern.cpp
    SOURCES kalmanfilter.h
    SOURCES kalmanfilter.cpp
    SOURCES sensordatahandler.h
    SOURCES sensordatahandler.cpp
)




# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appMotionBasedAuthentication PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appMotionBasedAuthentication
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appMotionBasedAuthentication
    PRIVATE Qt6::Quick
    Qt6::Sensors
)

include(GNUInstallDirs)
install(TARGETS appMotionBasedAuthentication
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
