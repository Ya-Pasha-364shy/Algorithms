cmake_minimum_required(VERSION 3.6)

project(linked_graph)

set(SOURCES test.cc)
set(LIBRARY Graph.cc)

add_library(lib_graph STATIC ${LIBRARY})

# add_library(dynamic_linked_list SHARED ${LIBRARY})

add_executable(test_graph ${SOURCES})

target_link_libraries(test_graph lib_graph)