cmake_minimum_required(VERSION 3.21)

message(STATUS "/explorations")

# Set project name #
project("explorations")

# Create the project as an executable #
set(asl ${PROJECT_NAME})
add_executable(${asl} main.c)

message("Created project executable " ${asl})

# Include sub directories #
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${asl} PUBLIC )  # TODO: add files here
