cmake_minimum_required(VERSION 3.6)
project(client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Mosquitto)

include_directories(${MOSQUITTO_INCLUDE_DIR})

set(SOURCE_FILES
        src/main.cpp
        src/CommandProcessor.cpp
        src/MQTTconfig.cpp
        src/application.cpp
        src/Tokenizer.cpp
        src/Topic.cpp)

add_executable(client ${SOURCE_FILES})

target_link_libraries (client mosquittopp)
