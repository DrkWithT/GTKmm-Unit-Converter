cmake_minimum_required(VERSION 3.10)

project("GTKmm_Demo1" VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(DEBUG_BUILD True)

if(DEBUG_BUILD)
    add_compile_options(-Wall -Wextra -Wpedantic -g -Og)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O2)
endif()

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_HOME_DIRECTORY}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/build")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtkmm-3.0)

include_directories("${CMAKE_HOME_DIRECTORY}/include")
add_subdirectory(src)

