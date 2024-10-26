cmake_minimum_required(VERSION 3.12)


project(first_hw)

add_executable(guess_the_number 
    main.cpp
    main.h
    take_usr_name.cpp
    take_usr_name.h    
    set_result.cpp
    set_result.h
    argument.cpp
    argument.h
)

add_compile_options(-g -Wall -Wextra -pedantic)

set_target_properties(guess_the_number PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)