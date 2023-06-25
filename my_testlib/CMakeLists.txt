cmake_minimum_required(VERSION 3.14)

project(my_testlib LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_library(my_testlib SHARED
  my_testlib_global.h
  my_testlib.cpp
  my_testlib.h
)

target_include_directories(my_testlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(my_testlib PRIVATE Qt${QT_VERSION_MAJOR}::Core
#    INTERFACE ${CMAKE_CURRENT_BINARY_DIR}
    )

target_compile_definitions(my_testlib PRIVATE MY_TESTLIB_LIBRARY)

#set_target_properties(my_testlib PROPERTIES RUNTIME_OUTPUT_DIRECTORY "D:\\code\\qt\\build-c_test-Desktop_Qt_6_1_3_MinGW_64_bit-Debug\\my_testlib")

#install(TARGETS my_testlib DESTINATION lib)
#install(FILES my_testlib.h DESTINATION include)
