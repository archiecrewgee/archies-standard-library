target_include_directories(${asl} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${asl}
    PRIVATE
        sort.c
)

message(STATUS "/algorithms")
