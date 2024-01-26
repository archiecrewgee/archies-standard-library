target_include_directories(${archies_standard_library} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${archies_standard_library}
    PRIVATE
        sort.c
)

message(STATUS "Added /algorithms")
