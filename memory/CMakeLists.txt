cmake_minimum_required(VERSION 3.21)

message(STATUS "/memory")

# Set project name #
project("test")

# Create the project as an executable #
set(PROJECT_EXECUTABLE ${PROJECT_NAME})
add_executable(${PROJECT_EXECUTABLE} "")

message("Created project executable " ${PROJECT_EXECUTABLE})

# Include sub directories #
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${PROJECT_EXECUTABLE} PUBLIC memory.c)


# add main.c to executable
target_sources(${PROJECT_EXECUTABLE} PRIVATE main.c)