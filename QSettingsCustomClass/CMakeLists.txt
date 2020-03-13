cmake_minimum_required(VERSION 3.5)

project(QSettingsCustomClass LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

add_executable(QSettingsCustomClass
    CustomClass.h
    CustomClass.cpp
    main.cpp
)
target_link_libraries(QSettingsCustomClass Qt5::Core)
