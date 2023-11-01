cmake_minimum_required(VERSION 3.0)

project(TheEscapists)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(main.out src/Time.cpp src/Inmate.cpp src/JobBoard.cpp src/Prison.cpp src/Data.cpp main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(main.out PRIVATE Threads::Threads)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(main.out PRIVATE nlohmann_json::nlohmann_json)
