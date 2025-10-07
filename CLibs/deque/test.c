#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "deque.h"

#define DEQ_MAX_ITEM_VALUE 100000
#define DEQ_MAX_LENGTH 10000

int main()
{
    int_deq_t *deq_test = deq_init();
    if (!deq_test) {
        return -1;
    }
    int tmp_rand, i, j;

    srand(time(NULL));

    for (i = 0; i < DEQ_MAX_LENGTH; i++) {
        tmp_rand = rand() % DEQ_MAX_ITEM_VALUE;
        if (tmp_rand % 2 == 0) {
            if (!deq_push_back(deq_test, tmp_rand)) {
                break;
            }
        } else {
            if (!deq_push_front(deq_test, tmp_rand)) {
                break;
            }
        }
    }
    assert(deq_test->size == DEQ_MAX_LENGTH);

    deq_pop_back(deq_test);
    deq_pop_back(deq_test);
    deq_pop_back(deq_test);

    deq_pop_front(deq_test);
    deq_pop_front(deq_test);
    deq_pop_front(deq_test);

    deq_sort(&deq_test);

    for (i = 0; i < DEQ_MAX_LENGTH/5; i++) {
        tmp_rand = rand() % DEQ_MAX_ITEM_VALUE;
        if (tmp_rand % 2 == 0) {
            if (!deq_push_back(deq_test, tmp_rand)) {
                break;
            }
        } else {
            if (!deq_push_front(deq_test, tmp_rand)) {
                break;
            }
        }
    }

    deq_sort(&deq_test);

    deq_pop_back(deq_test);
    deq_pop_front(deq_test);

    deq_destroy(deq_test);  

    return 0;
}