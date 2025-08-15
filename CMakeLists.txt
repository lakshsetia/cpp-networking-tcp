cmake_minimum_required(VERSION 3.27)

project(server-client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(utils)

add_executable(server server/server.cpp)
target_link_libraries(server PRIVATE utils)

add_executable(client client/client.cpp)
target_link_libraries(client PRIVATE utils)