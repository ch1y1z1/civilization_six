cmake_minimum_required(VERSION 3.0)

project(Civilization_6_1.0)

aux_source_directory(. DIR_SRCS)

add_subdirectory(src)

add_executable(Civilization_6 ${DIR_SRCS})

target_link_libraries(Civilization_6 prin)