cmake_minimum_required(VERSION 3.10)

project(otus-cpp-basic-async CXX)

find_package(Threads REQUIRED)

# Автоматическая загрузка и сборка TBB
# include(FetchContent)


# if (MINGW)
#     # set(CMAKE_SHARED_LINKER_FLAGS "")
#     # set(CMAKE_EXE_LINKER_FLAGS "")

#     set(TBB_ENABLE_PROFILING OFF CACHE BOOL "Disable ITT profiling in TBB")
#     add_definitions(-D_WIN32_WINNT=0x0601)
#     add_definitions(-DTBB_USE_GLIBCXX_VERSION=14000)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
#     set(CMAKE_SHARED_LINKER_FLAGS "")
#     set(CMAKE_EXE_LINKER_FLAGS "")
# endif()

# FetchContent_Declare(
#     tbb
#     GIT_REPOSITORY https://github.com/oneapi-src/oneTBB.git
#     # GIT_TAG        v2021.10.0
# )

# FetchContent_MakeAvailable(tbb)

# set(TBB_ENABLE_PROFILING OFF CACHE BOOL "Disable ITT profiling in TBB")


file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(src_file ${SRC_FILES})
    get_filename_component(target ${src_file} NAME_WLE)
    add_executable(${target} ${src_file})
    list(APPEND TARGETS ${target})
    message("target added: ${target}")
endforeach(src_file ${SRC_FILES})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message("Disable bench_par_stl")
    set_target_properties(bench_par_stl PROPERTIES EXCLUDE_FROM_ALL TRUE)
endif()

foreach(target ${TARGETS})
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${target} PRIVATE 
            -g
            -Wall
            -Wextra
            -Werror
            -Wno-unused-parameter
            -pedantic
        )
        if (${target} STREQUAL "bench_par_stl" AND
            CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            target_compile_options(${target} PRIVATE 
                -O3
            )
            target_link_libraries(${target} PUBLIC Threads::Threads tbb)
        else()
            target_link_libraries(${target} PUBLIC Threads::Threads)
        endif()
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${target} PRIVATE
            /EHsc
            /W4
        )
    endif()
    target_compile_features(${target} PUBLIC cxx_std_20)
endforeach(target IN ${TARGETS})
