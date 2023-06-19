cmake_minimum_required(VERSION 3.25)
project(avldictionary)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(avldictionary
        Dictionary.cpp
        iofmtguard.cpp)
