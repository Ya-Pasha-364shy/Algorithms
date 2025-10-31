#include <stdio.h>
#include <stdlib.h>

#include "set.h"

int main() {
    int_set_t *set = set_init_default();

    set_insert(set, 1);
    set_insert(set, 1);
    set_insert(set, 2);
    set_insert(set, 3);
    set_insert(set, 0);
    set_insert(set, -1);
    set_insert(set, 11);
    set_insert(set, 101);
    set_insert(set, 101);
    set_insert(set, 2);
    set_insert(set, 3);

    set_print(set);

    set_destroy(set);

    return 0;
}