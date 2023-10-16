cmake_minimum_required(VERSION 3.0)

project(TheEscapists)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(main.out src/Time.cpp src/Inmate.cpp src/JobBoard.cpp src/Prison.cpp main.cpp)