#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "set.h"

int_set_t *set_init(size_t N) {
    int_set_t *set = calloc(1, sizeof(int_set_t));
    if (!set) {
        fprintf(stderr, "<%s>: calloc failed: %s\n", __func__, strerror(errno));
        return NULL;
    }
    if (!N) {
        N = 1;
    }
    int_array_t *nested_arr = NULL;
    nested_arr = array_init(N);
    if (!nested_arr) {
        free(set);
        fprintf(stderr, "<%s>: failed to allocate nested array: %s\n", __func__,
                                                                      strerror(errno));
        return NULL;
    }
    set->payload = nested_arr;

    return set;
}

int_set_t *set_init_default() {
    return set_init(0);
}

void set_destroy(int_set_t *set) {
    array_destroy(set->payload);
    free(set);
}

bool set_insert(int_set_t *set, int value) {
    bool rc = false;

    if (!set_search(set, value)) {
        array_push_back(set->payload, value);
        rc = true;
    } else {
        rc = false;
    }

    return rc;
}
 
bool set_erase(int_set_t *set, int value) {
    return array_erase_value(set->payload, value);
}

bool set_search(int_set_t *set, int value) {
    return array_search(set->payload, value);
}

void set_print(int_set_t *set) {
    array_print(set->payload);
}