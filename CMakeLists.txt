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
# FetchContent_Declare(
#     my_dependency
#     SOURCE_DIR ${CMAKE_SOURCE_DIR}/third_party/my_dependency
# )
# FetchContent_MakeAvailable(my_dependency)

# Main target
add_executable(homeWork_7 
    main.cpp
    check_container.cpp
    # functions.h
    # move_me_out.cpp
    # move_me_out.h
)

# Test target
add_executable(
    test_list
    test/test_list.cpp
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