cmake_minimum_required(VERSION 2.6)

project(finite-state-machines)


enable_testing()

include_directories(fs_machine)

add_subdirectory( src build/src )
add_subdirectory( machines fs_machine )