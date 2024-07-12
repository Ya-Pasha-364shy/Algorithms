cmake_minimum_required(VERSION 3.6)

project(two_way_linked_list_obj)

set(SOURCES test.c)
set(LIBRARY listObj.c)

include_directories(${CMAKE_SOURCE_DIR})

add_library(static_linked_list_obj STATIC ${LIBRARY})

# add_library(dynamic_linked_list SHARED ${LIBRARY})

add_executable(linked_list_obj_test ${SOURCES})

target_link_libraries(linked_list_obj_test static_linked_list_obj)