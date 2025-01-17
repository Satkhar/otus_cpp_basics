cmake_minimum_required(VERSION 3.12)

project(hw_NUM)

add_executable(homeWork_NUM 
    main.cpp
    # functions.cpp
    # functions.h
    # move_me_out.cpp
    # move_me_out.h
)

set_target_properties(homeWork_NUM PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)