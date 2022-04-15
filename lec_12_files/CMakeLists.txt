cmake_minimum_required(VERSION 2.8.9)

if(POLICY CMP0048)
      cmake_policy(SET CMP0048 NEW)
endif()

project (projectname VERSION "1.1.0")
#configure_file(config.h.in config.h)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

#include_directories("/opt/homebrew/Cellar/boost/1.78.0_1/include")
add_executable(hw12 test.cpp)
