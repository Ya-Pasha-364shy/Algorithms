#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "linked_list_2.h"

#define LL_MAX_ITEM_VALUE 100000
#define LL_MAX_LENGTH 10000

int main()
{
    int_linked_list2_t *ll2_test = ll2_init();
    if (!ll2_test) {
        return -1;
    }
    int tmp_rand, i, j;

    srand(time(NULL));

    for (i = 0; i < LL_MAX_LENGTH; i++) {
        tmp_rand = rand() % LL_MAX_ITEM_VALUE;
        if (tmp_rand % 2 == 0) {
            if (!ll2_push_back(ll2_test, tmp_rand)) {
                break;
            }
        } else {
            j = rand() % (i+1);
            if (!ll2_insert(ll2_test, i-j, tmp_rand)) {
                break;
            }
        }
    }
    assert(ll2_test->size == LL_MAX_LENGTH);

    ll2_pop_back(ll2_test);
    ll2_pop_back(ll2_test);
    ll2_pop_back(ll2_test);
    ll2_erase_value(ll2_test, 100);
    ll2_erase_value(ll2_test, 1000);
    ll2_erase_value(ll2_test, 56);
    ll2_erase_value(ll2_test, __INT_MAX__);
    ll2_erase_value_by_idx(ll2_test, 0);
    ll2_erase_value_by_idx(ll2_test, ll2_test->size-1);
    ll2_erase_value_by_idx(ll2_test, ll2_test->size/2);
    
    ll2_sort(&ll2_test);

    for (i = 0; i < LL_MAX_LENGTH/4; i++) {
        tmp_rand = rand() % LL_MAX_ITEM_VALUE;
        if (tmp_rand % 2 == 0) {
            if (!ll2_push_back(ll2_test, tmp_rand)) {
                break;
            }
        } else {
            j = rand() % (i+1);
            if (!ll2_insert(ll2_test, i-j, tmp_rand)) {
                break;
            }
        }
    }

    ll2_sort(&ll2_test);

    ll2_pop_back(ll2_test);
    ll2_erase_value_by_idx(ll2_test, ll2_test->size/2);
    ll2_pop_back(ll2_test);
    ll2_erase_value_by_idx(ll2_test, ll2_test->size/2);
    ll2_pop_back(ll2_test);
    ll2_erase_value_by_idx(ll2_test, ll2_test->size/2);
    ll2_pop_back(ll2_test);
    ll2_erase_value_by_idx(ll2_test, ll2_test->size/2);
    ll2_pop_back(ll2_test);

    ll2_destroy(ll2_test);

    return 0;
}