#include <stdio.h>

#include "array.h"

int main(void) {
    int_array_t *array = array_init_default();

    array_push_back(array, 1);
    array_push_back(array, 2);
    array_push_back(array, 3);
    array_push_back(array, 4);
    array_push_back(array, 5);

    array_print(array);

    int value_to_erase = 5;
    if (array_erase_value(array, value_to_erase)) {
        printf("%d erased from array !\n", value_to_erase);
    }
    if (!array_erase_value(array, value_to_erase)) {
        printf("%d CANNOT BE erased from array !\n", value_to_erase);
    }

    array_print(array);

    array_insert(array, 1, 10);
    array_insert(array, 2, 20);
    array_insert(array, 0, 30);

    array_print(array);

    value_to_erase = 20;
    if (array_erase_value(array, value_to_erase)) {
        printf("%d erased from array !\n", value_to_erase);
    }
    value_to_erase = 30;
    if (array_erase_value(array, value_to_erase)) {
        printf("%d erased from array !\n", value_to_erase);
    }

    array_print(array);
    array_insert(array, 100, 100);

    printf("before sort: ");
    array_print(array);

    array_sort(array);

    printf("after sort: ");
    array_print(array);

    value_to_erase = 10;
    if (array_erase_value(array, value_to_erase)) {
        printf("%d erased from array !\n", value_to_erase);
    }
    array_print(array);

    for (int i = 0; i < array->M; i++) {
        if (array_bin_search(array, array->payload[i]) != true) {
            printf("Failed to find: %d by binary search in array !\n", array->payload[i]);
        } else {
            printf("%d finded !\n", array->payload[i]);
        }
    }

    array_insert(array, 4, 5);
    array_pop_back(array);
    array_print(array);

    array_push_back(array, 12);
    array_insert(array, 3, 100);

    if (array_search(array, 3)) {
        printf("success: item finded !");
    }

    array_destroy(array);

    return 0;
}
