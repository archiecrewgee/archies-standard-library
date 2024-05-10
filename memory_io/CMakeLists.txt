if (DEFINED CONFIG_CMAKE_MEMORY_IO_ENABLE)
    message(STATUS "/memory_io")

    target_include_directories(${asl} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_sources(${asl} PUBLIC memory_io.c)
endif ()