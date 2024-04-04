add_executable(demoapp main.cpp)

add_subdirectory(app)
add_subdirectory(utils)

target_include_directories(demoapp PRIVATE "${GTK_INCLUDE_DIRS}")
target_link_directories(demoapp PRIVATE "${CMAKE_HOME_DIRECTORY}/build" PRIVATE "${GTK_LIBRARY_DIRS}")
target_link_libraries(demoapp PRIVATE app PRIVATE utils PRIVATE "${GTK_LIBRARIES}")
target_compile_options(demoapp PRIVATE "${GTK_CFLAGS_OTHER}")
