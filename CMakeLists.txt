cmake_minimum_required(VERSION 3.12)

project(hw_7)

if (MSVC)
    # @see https://github.com/google/googletest/blob/master/googletest/README.md
    # Visual Studio Dynamic vs Static Runtimes
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# Build googletest
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest" 
    "googletest"
)

# Main target
add_executable(homeWork_7 
    src/main.cpp
    src/check_container.cpp
    src/containerSerial.hpp
    src/containerList.hpp
)

# Test target
add_executable(
    test_list
    test/list_container_test.cpp
    test/serial_container_test.cpp
)

# Add src to the include directories for the test target
target_include_directories(
    test_list PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Link test target against gtest libraries
target_link_libraries(
    test_list PRIVATE
    gtest gtest_main
)

set_target_properties(homeWork_7 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(test_list PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED ON
)


if (MSVC)
    target_compile_options(
        homeWork_7 PRIVATE
        /W4
    )
    target_compile_options(
        test_list PRIVATE
        /W4
    )
else ()
    target_compile_options(
        homeWork_7 PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(
        test_list PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()