cmake_minimum_required(VERSION 3.6)

project(two_way_linked_list)

set(SOURCES test.c)
set(LIBRARY list.c)

add_library(static_linked_list STATIC ${LIBRARY})

# add_library(dynamic_linked_list SHARED ${LIBRARY})

add_executable(linked_list_test ${SOURCES})

target_link_libraries(linked_list_test static_linked_list)