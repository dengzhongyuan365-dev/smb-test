cmake_minimum_required(VERSION 3.13)
project(smb-test VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core DBus REQUIRED)

add_subdirectory(service)
add_subdirectory(client)