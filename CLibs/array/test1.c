#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "array.h"

#define ARR_MAX_LENGTH 1000
#define ARR_MAX_ITEM_VALUE 10000

int main()
{
    int_array_t *arr_test = array_init_default();
    if (!arr_test) {
        return -1;
    }
    int tmp_rand, i, j;

    srand(time(NULL));

    for (i = 0; i < ARR_MAX_LENGTH; i++) {
        tmp_rand = rand() % ARR_MAX_ITEM_VALUE;
        if (tmp_rand % 2 == 0) {
            if (!array_push_back(arr_test, tmp_rand)) {
                break;
            }
        } else {
            j = rand() % (i+1);
            if (!array_insert(arr_test, i-j, tmp_rand)) {
                break;
            }
        }
    }
    assert(arr_test->M == ARR_MAX_LENGTH);

    for (i = 0; i < ARR_MAX_LENGTH/2; i++) {
        tmp_rand = rand() % ARR_MAX_ITEM_VALUE;
        array_erase_value(arr_test, tmp_rand);
    }

    array_pop_back(arr_test);
    array_pop_back(arr_test);
    array_pop_back(arr_test);
    array_erase_value(arr_test, 100);
    array_erase_value(arr_test, 1000);
    array_erase_value(arr_test, 56);
    array_erase_value(arr_test, __INT_MAX__);
    array_erase_value_by_idx(arr_test, 0);
    array_erase_value_by_idx(arr_test, arr_test->M-1);
    array_erase_value_by_idx(arr_test, arr_test->M/2);
    
    array_sort(arr_test);

    for (i = 0; i < ARR_MAX_LENGTH/4; i++) {
        tmp_rand = rand() % ARR_MAX_ITEM_VALUE;
        array_erase_value(arr_test, tmp_rand);
    }

    array_sort(arr_test);

    array_destroy(arr_test);

    return 0;
}