cmake_minimum_required(VERSION 3.5)

project(UD VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql PrintSupport)

# Project sources
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    login.h login.cpp login.ui
    addrecord.cpp addrecord.h addrecord.ui
    anothertable.cpp anothertable.h anothertable.ui
    changerecord.cpp changerecord.h changerecord.ui
    print.h print.cpp print.ui
    qcustomplot.h qcustomplot.cpp
    printgraph.cpp printgraph.h printgraph.ui
    qcpdocumentobject.cpp qcpdocumentobject.h
)

# Set executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(UD MANUAL_FINALIZATION ${PROJECT_SOURCES})
else()
    add_executable(UD ${PROJECT_SOURCES})
endif()

# Link libraries
target_link_libraries(UD PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::PrintSupport

)

# Additional properties
set_target_properties(UD PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(UD PRIVATE ${CMAKE_SOURCE_DIR})


# Installation
install(TARGETS UD
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Finalize for Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(UD)
endif()
