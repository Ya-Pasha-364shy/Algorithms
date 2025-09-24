#ifndef LL_TWO_WAY_HEADER_H
#define LL_TWO_WAY_HEADER_H

#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

typedef struct int_linked_list_node_s {
    struct int_linked_list_node_s *next_node;
    struct int_linked_list_node_s *prev_node;
    int payload;
} int_linked_list_node2_t;

typedef struct int_linked_list_s {
    // pointer on sentinel node, exists always
    int_linked_list_node2_t *sentinel_node;
    // pointer on last exists member (exists if size >= 1)
    int_linked_list_node2_t *last_node;
    // capacity
    size_t size;
} int_linked_list2_t;

/// @brief Initialize linked list with sentinel element
/// @return Pointer on memory with type int_linked_list2_t
int_linked_list2_t *ll2_init();

/// @brief Frees memory that was occupied by int linked list object
/// @param ll Object to destroy
void ll2_destroy(int_linked_list2_t *ll);

/// @brief Adds to end of linked list new item
/// @param ll Object into which push_back will be performed
/// @param value Item to be placed into linked list
/// @return `true` if push_back performed successfully, `false` - otherwise
bool ll2_push_back(int_linked_list2_t *ll, int value);

/// @brief Inserts value at index in linked list
/// @param ll Object into which insertion will be performed
/// @param index Index for insert value
/// @param value Value for insert at index
/// @return `true` if insert performed successfully, `false` - otherwise
bool ll2_insert(int_linked_list2_t *ll, size_t index, int value);

/// @brief Removes last item in linked list
/// @param ll Object into which pop_back be performed
/// @return Value at the end
int ll2_pop_back(int_linked_list2_t *ll);

/// @brief Finds first occurence of a value in linked list and removes it
/// @param ll Object into which erasing will be performed
/// @param value_to_erase Value to erase
/// @return `true` if value was erased, `false` - otherwise
bool ll2_erase_value(int_linked_list2_t *ll, int value_to_erase);

/// @brief Erase value by index in linked list
/// @param ll Object into which erasing will be performed
/// @param index Index at which erasure will be performed
void ll2_erase_value_by_idx(int_linked_list2_t *ll, int index);

/// @brief Prints all items of linked list with new-line symbol at the end
/// @param ll Object in which embedded payload will be output
void ll2_print(int_linked_list2_t *ll);

/// @brief Sorts passed linked list using "selection sort" method in O(N^2)
/// @param ll Object in which payload will be sorted
void ll2_sort(int_linked_list2_t **ll);

/// @brief Finds passed item in passed array by linear search method in O(N)
/// @param ll Object in which embedded payload will be searched
/// @param sv Value to search
/// @return positive integer if value was founded, `-1` - otherwise
int ll2_search_value(int_linked_list2_t *ll, int sv);

#endif // LL_TWO_WAY_HEADER_H