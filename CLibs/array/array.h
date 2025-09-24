#ifndef ARRAY_HEADER_H
#define ARRAY_HEADER_H

#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

typedef struct int_array_s {
    int *payload;
    // capacity
    size_t N;
    // size, M-1 - last index 
    size_t M;
    // set to `true` after sorting operation, `false` after inserting
    bool is_sorted;
} int_array_t;

/// @brief Initialize array of N items
/// @param N Number of items to allocate in array
/// @return Pointer on memory with type int_array_t
int_array_t *array_init(size_t N);

/// @brief Initialize array of 1 item
/// @return Pointer on memory with type int_array_t
int_array_t *array_init_default();

/// @brief Frees memory that was occupied by int array object
/// and embedded payload
/// @param array Object to destroy
void array_destroy(int_array_t *array);

/// @brief Adds to end of array new item 
/// @param array Object into which push_back will be performed
/// @param value Item to be placed into array
/// @return `true` if value was pushed successfully, `false` - otherwise
bool array_push_back(int_array_t *array, int value);

/// @brief Inserts value at index in array
/// @param array Object into which insertion will be performed
/// @param index Index for insert value
/// @param value Value for insert at index
/// @return `true` if value at index was successfully inserted, `false` - otherwise
bool array_insert(int_array_t *array, size_t index, int value);

/// @brief Removes last item in array
/// @param array Object into which pop_back will be performed
/// @return Value at the end 
int array_pop_back(int_array_t *array);

/// @brief Finds first occurence of a value in array and removes it
/// @param array Object into which erasing will be performed
/// @param value_to_erase Value to erase
/// @return `true` if value was erased, `false` - otherwise
bool array_erase_value(int_array_t *array, int value_to_erase);

/// @brief Erase value by index in array
/// @param array Object into which erasing will be performed
/// @param index Index at which erasure will be performed
void array_erase_value_by_idx(int_array_t *array, size_t index);

/// @brief Prints all items of array with new-line symbol
/// @param array Object in which embedded payload will be output
void array_print(int_array_t *array);

/// @brief Sorts passed array using "quicksort" method in O(N*log(N))
/// @param array Object in which embedded payload will be sorted 
void array_sort(int_array_t *array);

/// @brief Finds passed item in passed array by binary search method in O(log(N))
/// @param array Object in which embedded payload will be searched
/// @param search_value Value to search
/// @return `true` if value was finded, `false` - otherwise
bool array_bin_search(int_array_t *array, int search_value);

/// @brief Finds passed item in passed array by linear search
///        if array isn't sorted and by binary search" - otherwise.
/// @param array Object in which embedded payload will be searched
/// @param search_value Value to search
/// @return `true` if value was finded, `false` - otherwise
bool array_search(int_array_t *array, int search_value);

#endif // ARRAY_HEADER_H