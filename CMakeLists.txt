cmake_minimum_required(VERSION 3.16)
project(random_events)
set(RANDOM_EVENTS_VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src/random_events)
add_subdirectory(src/client_program)
add_subdirectory(test)