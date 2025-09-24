#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "linked_list.h"

#define LL_MAX_ITEM_VALUE 10000
#define LL_MAX_LENGTH 1000

int main()
{
    int_linked_list_t *ll_test = ll_init();
    if (!ll_test) {
        return -1;
    }
    int tmp_rand, i, j;

    srand(time(NULL));

    for (i = 0; i < LL_MAX_LENGTH; i++) {
        tmp_rand = rand() % LL_MAX_ITEM_VALUE;
        if (tmp_rand % 2 == 0) {
            if (!ll_push_back(ll_test, tmp_rand)) {
                break;
            }
        } else {
            j = rand() % (i+1);
            if (!ll_insert(ll_test, i-j, tmp_rand)) {
                break;
            }
        }
    }
    assert(ll_test->size == LL_MAX_LENGTH);

    ll_pop_back(ll_test);
    ll_pop_back(ll_test);
    ll_pop_back(ll_test);
    ll_erase_value(ll_test, 100);
    ll_erase_value(ll_test, 1000);
    ll_erase_value(ll_test, 56);
    ll_erase_value(ll_test, __INT_MAX__);
    ll_erase_value_by_idx(ll_test, 0);
    ll_erase_value_by_idx(ll_test, ll_test->size-1);
    ll_erase_value_by_idx(ll_test, ll_test->size/2);
    
    ll_sort(&ll_test);
    ll_destroy(ll_test);

    return 0;
}