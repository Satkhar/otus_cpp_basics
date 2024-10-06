cmake_minimum_required(VERSION 3.12)

project(first_hw)

add_executable(homeWork01 
    main.cpp
    functions.cpp
    functions.h
    move_me_out.cpp
    move_me_out.h
)

set_target_properties(homeWork01 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)