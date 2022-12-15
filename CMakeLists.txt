cmake_minimum_required(VERSION 3.0)

project(Civilization_6_1.0)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_definitions("-g -Wall -std=c++2a")

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/ SOURCE_ALL)

add_executable(main main.cpp ${SOURCE_ALL})