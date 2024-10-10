cmake_minimum_required(VERSION 3.12)


project(first_hw)

add_executable(module_link_hw 
    main.cpp
    main.h
    take_usr_name.cpp
    take_usr_name.h    
    set_result.cpp
    set_result.h
)

set_target_properties(module_link_hw PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)