cmake_minimum_required(VERSION 3.21)

message(STATUS "/explorations")

# Set project name #
project("explorations")

# Create the project as an executable #
set(asl ${PROJECT_NAME})
add_executable(${asl} main.c)

message("Created project executable " ${asl})

# Include sub directories #


# Add external directories #
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../helpers external_directories/helpers)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../memory external_directories/memory)
