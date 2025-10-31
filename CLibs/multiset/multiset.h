#ifndef _MULTISET_HEADER_H_
#define _MULTISET_HEADER_H_

#include <stdbool.h>

#include "array.h"

typedef struct int_multiset_node_s {
    int_array_t *payload_per_batch;
} int_multiset_node_t;

typedef struct int_multiset_s {
    int_multiset_node_t *batches;
    // max size of multiset
    int N;
    // occupancy rate
    float k;
} int_multiset_t;

int_multiset_t *ms_init(int N);

int_multiset_t *ms_init_default();

void ms_destroy(int_multiset_t **ms);

bool ms_start_push(int_multiset_t *ms);
bool ms_push(int_multiset_t *ms, int value);
bool ms_finish_push(int_multiset_t *ms);

bool ms_start_erase(int_multiset_t *ms);
bool ms_erase(int_multiset_t *ms, int value);
bool ms_finish_erase(int_multiset_t *ms);

void ms_print(int_multiset_t *ms);

int ms_search_value(int_multiset_t *ms, int sv);

#endif // _MULTISET_HEADER_H_