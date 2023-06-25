cmake_minimum_required(VERSION 3.5)

project(PostMessage VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Concurrent REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Concurrent REQUIRED)

add_subdirectory(my_testlib)

link_directories(${CMAKE_CURRENT_BINARY_DIR}/my_testlib)

file(GLOB UI_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        worker.h worker.cpp
        ${UI_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PostMessage
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PostMessage APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PostMessage SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PostMessage
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(PostMessage PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Concurrent
    my_testlib
    )

set_target_properties(PostMessage PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PostMessage)
endif()

add_subdirectory(LibTest)

#if(WIN32)
#    if(MSVC)
#        set_target_properties(${PROJECT_NAME} PROPERTIES
#            WIN32_EXECUTABLE YES
#            LINK_FLAGS "/ENTRY:mainCRTStartup"
#            )
#    elseif(CMAKE_COMPILER_IS_GNUCXX)
#        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
#    else()
#        message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
#    endif(MSVC)
#elseif(APPLE)
#    set_target_properties(${PROJECT_NAME} PROPERTIES
#        MACOSX_BUNDLE YES
#        )
#elseif(UNIX)
#    # Nothing special required
#else()
#    message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
#endif(WIN32)
