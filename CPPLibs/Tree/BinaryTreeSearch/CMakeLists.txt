cmake_minimum_required(VERSION 3.5.1)

project(binary_tree_search)

set(SOURCES test.cc)
set(LIBRARY BTS.cc)

add_library(lib_bts STATIC ${LIBRARY})

# add_library(dynamic_linked_list SHARED ${LIBRARY})

add_executable(test_bts ${SOURCES})

target_link_libraries(test_bts lib_bts)