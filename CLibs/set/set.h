#ifndef _SET_HEADER_H_
#define _SET_HEADER_H_

#include <stdbool.h>
#include "array.h"

typedef struct int_set_s {
    int_array_t *payload;
} int_set_t;

int_set_t *set_init(size_t N);

int_set_t *set_init_default();

void set_destroy(int_set_t *set);

bool set_insert(int_set_t *set, int value);

bool set_erase(int_set_t *set, int value);

bool set_search(int_set_t *set, int value);

void set_print(int_set_t *set);

#endif // _SET_HEADER_H_