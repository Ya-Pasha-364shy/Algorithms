#include <stdio.h>
#include <stdlib.h>

#include "array.h"

int main() {
    int_array_t *a = array_init_default();

    array_push_back(a, 1);
    array_push_back(a, 2);
    array_push_back(a, 3);
    array_push_back(a, 4);
    array_push_back(a, 40);
    array_push_back(a, 30);
    array_push_back(a, 20);
    array_push_back(a, 10);
    array_push_back(a, 9);
    array_push_back(a, 8);
    array_push_back(a, 7);
    array_push_back(a, 6);
    array_push_back(a, 5);
    array_push_back(a, 4);
    array_push_back(a, 3);
    array_push_back(a, 2);
    array_push_back(a, 1);
    array_push_back(a, 11);

    array_print(a);
    array_advanced_bubble_sort(a);
    array_print(a);

    if (!array_erase_value(a, 11)) {
        printf("failed to erase 11");
    }
    if (!array_erase_value(a, 2)) {
        printf("failed to erase 2");
    }
    if (!array_erase_value(a, 1)) {
        printf("failed to erase 1");
    }
    if (!array_erase_value(a, 40)) {
        printf("failed to erase 40");
    }

    array_print(a);
    array_destroy(&a);
    array_print(a);
    
    return 0;
}