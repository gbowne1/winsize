cmake_minimum_required(VERSION 3.10)
project(ConsoleUtility)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES main.cpp src/Console.cpp)

include_directories(include)

add_executable(console_app ${SOURCES})

