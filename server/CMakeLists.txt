cmake_minimum_required(VERSION 3.10)
project(tcp_chat_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

include_directories(../chatillo/include)
link_libraries(chatillo)

#server
set(SERVER_SRC
        src/main.cpp
        src/server.cpp)

add_executable(server ${SERVER_SRC})