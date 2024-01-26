cmake_minimum_required(VERSION 3.21)

message(STATUS "/memory")

# Set project name #
project("archies_standard_library")

# Create the project as an executable #
set(asl ${PROJECT_NAME})
add_executable(${asl} main.c)

message("Created project executable " ${asl})

# Include sub directories #
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${asl} PUBLIC memory.c)

# add swapping functionality
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../algorithms external/algorithms)