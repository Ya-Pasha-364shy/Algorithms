#ifndef _DEQUE_HEADER_H_
#define _DEQUE_HEADER_H_

#include <stdbool.h>

typedef struct int_deq_node_s {
    struct int_deq_node_s *next_node;
    struct int_deq_node_s *prev_node;
    int payload;
} int_deq_node_t;

typedef struct int_deq_s {
    // pointer on sentinel node, exists always
    int_deq_node_t *sentinel_node;
    // pointer on last exists member (exists if size >= 1)
    int_deq_node_t *last_node;
    // capacity
    size_t size;
} int_deq_t;

/// @brief Initialize deque (based on two-way linked list)
/// with sentinel element
/// @return Pointer on memory with type int_deq_node_t
int_deq_t *deq_init();

/// @brief Frees memory that was occupied by int deque object
/// @param deq Object to destroy
void deq_destroy(int_deq_t *deq);

/// @brief Adds to end of deque new item
/// @param deq Object into which push_back will be performed
/// @param value Item to be placed into deque
/// @return `true` if push_back performed successfully, `false` - otherwise
bool deq_push_back(int_deq_t *deq, int value);

/// @brief Adds to begin of deque new item
/// @param deq Object into which push_front will be performed
/// @param value Item to be placed into deque
/// @return `true` if push_front performed successfully, `false` - otherwise
bool deq_push_front(int_deq_t *deq, int value);

/// @brief Removes and returns last item in deque
/// @param deq Object into which pop_back be performed
/// @return Value at the end
int deq_pop_back(int_deq_t *deq);

/// @brief Removes and returns first item in deque
/// @param deq Object into which pop_front be performed
/// @return Value at the beginning of deque
int deq_pop_front(int_deq_t *deq);

/// @brief Prints all items of deque with new-line symbol at the end
/// @param deq Object in which embedded payload will be output
void deq_print(int_deq_t *deq);

/// @brief Sorts passed deque using "selection sort" method in O(N^2)
/// @param deq Object in which payload will be sorted
void deq_sort(int_deq_t **deq);

/// @brief Finds first occurrence of passed item in passed linked list
/// by linear search method in O(N)
/// @param ll Object in which embedded payload will be searched
/// @param sv Value to search
/// @return index of first occurrence of value in
/// deque if it was founded, `-1` - otherwise
int deq_search_value(int_deq_t *deq, int sv);

#endif // _DEQUE_HEADER_H_