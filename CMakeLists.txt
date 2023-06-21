cmake_minimum_required(VERSION 3.25)
project(avldictionary)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(avldictionary
        Dictionary.cpp
        IOFormatGuard.cpp
        Command.cpp
        main.cpp
        UserInterface.cpp)
