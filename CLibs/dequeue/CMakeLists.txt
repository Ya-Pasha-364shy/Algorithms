cmake_minimum_required(VERSION 3.6)

project(dequeue)

# set(SOURCES test.c)
set(LIBRARY queue.c)

add_library(static_dequeue STATIC ${LIBRARY})

# add_library(dynamic_linked_list SHARED ${LIBRARY})

# add_executable(dequeue_test ${SOURCES})

# target_link_libraries(dequeue_test static_dequeue)