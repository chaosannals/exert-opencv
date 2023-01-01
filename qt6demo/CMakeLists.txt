cmake_minimum_required(VERSION 3.5)

project(qt6demo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES qt6demo_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qt6demo
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET qt6demo APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(qt6demo SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(qt6demo
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# OPENCV
set(WITH_QT ON)
set(BUILD_PERF_TESTS OFF)
set(BUILD_TESTS OFF)
set(BUILD_opencv_python_tests OFF)
set(BUILD_JAVA OFF)
set(OPENCL_FOUND OFF)
set(OPENCV_DNN_OPENCL OFF)
set(WITH_OPENCL OFF)
set(WITH_OPENCLAMDBLAS OFF)
set(WITH_OPENCLAMDFFT OFF)
set(WITH_OPENCL_D3D11_NV OFF)
set(WITH_OPENCL_SVM OFF)
add_subdirectory("${PROJECT_SOURCE_DIR}/opencv")
target_include_directories(
    qt6demo
    PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/opencv/modules/core/include"
    "${PROJECT_SOURCE_DIR}/opencv/modules/highgui/include"
    "${PROJECT_SOURCE_DIR}/opencv/modules/imgcodecs/include"
    "${PROJECT_SOURCE_DIR}/opencv/modules/videoio/include"
)
target_link_directories(qt6demo PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/opencv/lib")
file(GLOB QT6DEMO_OPENCV_LINK_LIBS "${CMAKE_CURRENT_BINARY_DIR}/opencv/lib/*")

message(STATUS ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS ${QT6DEMO_OPENCV_LINK_LIBS})

target_link_libraries(qt6demo PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${QT6DEMO_OPENCV_LINK_LIBS})

set_target_properties(qt6demo PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS qt6demo
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qt6demo)
endif()
