#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>

#include "testlib.h"

/*
 * Your goal in this kata is to implement a difference function,
 * which subtracts one list from another and returns the result.
 * 
 * It should remove all values from list a,
 * which are present in list b keeping their order.
*/
bool is_exists(int element, const int * arr, size_t arr_size)
{
	for (size_t array_counter = 0; array_counter != arr_size; array_counter++)
	{
		if (element == arr[array_counter])
			return true;
	}
	return false;
}

int * array_diff(const int *arr1, size_t n1, const int *arr2, size_t n2, size_t *z)
{
	if (n1 < 0)
		return NULL;

	size_t array_counter = 0;
	size_t remembered_items_counter = 0;
	int    remembered_items[n1];
	size_t difference_of_arrays_counter = 0;
	int *  difference_of_arrays = (int *)malloc(n1 * sizeof(int));

	for (; array_counter < n2; array_counter++)
	{
		if (is_exists(arr2[array_counter], arr1, n1))
		{
			remembered_items[remembered_items_counter++] = arr2[array_counter];
		}
	}

	for (array_counter = 0; array_counter < n1; array_counter++)
	{
		if (is_exists(arr1[array_counter], remembered_items, remembered_items_counter))
		{
			continue;
		}
		difference_of_arrays[difference_of_arrays_counter++] = arr1[array_counter];
	}

	*z = difference_of_arrays_counter;
	return difference_of_arrays;
}

int main()
{
	const int arr1[5] = {1, 2, 3, 4, 5};
	const int arr2[3] = {1, 3, 4};
	const int expected[2] = {2, 5};

	size_t z;
	int * result = array_diff(arr1, 5, arr2, 3, &z);
	if (2 == z)
	{
		IS_ARRS_EQUALS(result, expected, 2);
		if (arrays_are_equals)
			printf("Arrays are equal !\n");
		else
			printf("Arrays arent equal !\n");
	}

	free(result);
	return 0;
}