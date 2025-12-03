cmake_minimum_required(VERSION 3.10)
project(ringbuffer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Library
add_library(ringbuffer_lib
    src/ring_buffer.cpp
)

target_include_directories(ringbuffer_lib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Download and configure Google Test
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

enable_testing()

# Test executable
add_executable(tests
    tests/test_ring_buffer.cpp
)

target_link_libraries(tests
    ringbuffer_lib
    gtest_main
)

add_test(NAME ring_buffer_tests COMMAND tests)

# Main application executable
add_executable(ringbuffer_app
    app/main.cpp
)

target_link_libraries(ringbuffer_app
    ringbuffer_lib
)
