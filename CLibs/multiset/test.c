#include <stdio.h>
#include <stdlib.h>

#include "multiset.h"

int main() {
    int_multiset_t *ms = ms_init_default();

    ms_start_push(ms);
    ms_push(ms, 1);
    ms_push(ms, 2);
    ms_push(ms, 3);
    ms_push(ms, 4);
    ms_push(ms, 40);
    ms_push(ms, 30);
    ms_push(ms, 20);
    ms_push(ms, 10);
    ms_push(ms, 9);
    ms_push(ms, 8);
    ms_push(ms, 7);
    ms_push(ms, 6);
    ms_push(ms, 5);
    ms_push(ms, 4);
    ms_push(ms, 3);
    ms_push(ms, 2);
    ms_push(ms, 1);
    ms_push(ms, 11);
    ms_print(ms);
    ms_finish_push(ms);

    ms_print(ms);

    ms_start_erase(ms);
    ms_erase(ms,11);
    ms_erase(ms,2);
    ms_erase(ms,1);
    ms_erase(ms,40);
    ms_finish_erase(ms);

    ms_print(ms);

    ms_destroy(&ms);

    ms_print(ms);

    return 0;
}