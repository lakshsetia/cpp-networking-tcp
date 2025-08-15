add_library(utils Socket.cpp WSA.cpp)

target_link_libraries(utils PRIVATE ws2_32)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})