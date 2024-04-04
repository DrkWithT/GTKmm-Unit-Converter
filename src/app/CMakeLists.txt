add_library(app "")

target_sources(app PRIVATE appwindow.cpp)
target_include_directories(demoapp PRIVATE "${GTK_INCLUDE_DIRS}")
target_link_directories(demoapp PRIVATE "${CMAKE_HOME_DIRECTORY}/build" PRIVATE "${GTK_LIBRARY_DIRS}")
target_link_libraries(app PRIVATE utils PUBLIC PkgConfig::GTK)

