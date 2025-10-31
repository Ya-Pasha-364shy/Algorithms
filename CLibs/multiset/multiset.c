#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#include "multiset.h"

static inline int ms_hash(int N, int value) {
    return value % N;
}

static bool ms_update_occupancy_rate(int_multiset_t *ms) {
    int_array_t *payload_on_batch = NULL;
    float batch_N = 0.0f, batch_M = 0.0f;
    float sum_k = 0.0f;
    int i;

    for (i = 0; i < ms->N; i++) {
        payload_on_batch = ms->batches[i].payload_per_batch;

        batch_N = payload_on_batch->N;
        batch_M = payload_on_batch->M;
        if (!batch_M || !batch_N) {
            continue;
        }
        sum_k += batch_M / batch_N;
    }
    ms->k = sum_k / ms->N;
    return true;
}

static bool ms_extend(int_multiset_t *ms) {
    if (ms->k < 0.5) {
        return true;
    }
    size_t old_N, tmp_idx = 0, tmp_len;
    int new_N = ms->N * 2, tmp_value;
    int_multiset_node_t *batches = ms->batches;

    batches = (int_multiset_node_t *)realloc(batches, new_N * sizeof(int_multiset_node_t));
    if (!batches) {
        fprintf(stderr, "<%s>: failed extend batches: %s\n", __func__, strerror(errno));
        return false;
    }
    ms->batches = batches;
    old_N = ms->N;
    ms->N = new_N;

    int_array_t *items_to_remove = array_init_default();

    for (size_t i = 0; i < old_N; i++) {
        int_array_t *tmp_arr = batches[i].payload_per_batch;
        tmp_len = tmp_arr->M;
        for (size_t j = 0; j < tmp_len; j++) {
            tmp_value = tmp_arr->payload[j];
            tmp_idx = ms_hash(new_N, tmp_value);
            if (tmp_idx != i) {
                array_push_back(items_to_remove, tmp_value);
                if (!batches[tmp_idx].payload_per_batch) {
                    batches[tmp_idx].payload_per_batch = array_init_default();
                    if (!batches[tmp_idx].payload_per_batch) {
                        fprintf(stderr, "<%s>: failed create new batch for push value '%d'\n", __func__,
                                        tmp_value);
                        return false;
                    }
                }
                if (!array_push_back(batches[tmp_idx].payload_per_batch, tmp_value)) {
                    fprintf(stderr, "<%s>: failed to push value '%d' at new batch: %s\n", __func__,
                                    tmp_value, strerror(errno));
                    return false;
                }
            }
        }
        for (size_t i = 0; i < items_to_remove->M; i++) {
            array_erase_value(tmp_arr, items_to_remove->payload[i]);
        }
        array_clean_all(items_to_remove);
    }
    array_destroy(&items_to_remove);

    if (!ms_update_occupancy_rate(ms)) {
        fprintf(stderr, "<%s>: failed re-calc occupancy rate after extend, "
                        "all memory was freed\n", __func__);
        return false;
    }

    return true;
}

int_multiset_t *ms_init(int N) {
    int_multiset_t *ms = (int_multiset_t *)calloc(1, sizeof(int_multiset_t));
    int i;

    if (!ms) {
        fprintf(stderr, "<%s>: calloc failed: %s\n", __func__, strerror(errno));
        return NULL;
    }
    if (!N) {
        N = 1;
    }
    ms->N = N;
    ms->batches = (int_multiset_node_t *)calloc(N, sizeof(int_multiset_node_t));
    if (!ms->batches) {
        free(ms);
        fprintf(stderr, "<%s>: calloc failed: %s\n", __func__, strerror(errno));
        return NULL;
    }
    for (i = 0; i < N; i++) {
        ms->batches[i].payload_per_batch = array_init_default();
        if (!ms->batches[i].payload_per_batch) {
            fprintf(stderr, "<%s>: failed to alloc batch at #%d: %s\n", __func__, i+1, strerror(errno));
            goto free_batches;
        }
    }
    return ms;

free_batches:
    for (int j = 0; j < i; j++) {
        array_destroy(&ms->batches[j].payload_per_batch);
    }
    free(ms->batches);
    free(ms);

    return NULL;
}

int_multiset_t *ms_init_default() {
    return ms_init(0);
}

void ms_destroy(int_multiset_t **ms) {
    if (!ms) {
        return;
    }
    int_multiset_t *_ms = *ms;
    if (!_ms) {
        return;
    }

    for (int i = 0; i < _ms->N; i++) {
        array_destroy(&_ms->batches[i].payload_per_batch);
    }
    free(_ms->batches);
    free(_ms);

    *ms = NULL; 
}

bool ms_start_push(int_multiset_t *ms) {
    if (!ms) {
        fprintf(stderr, "<%s>: invalid multiset\n", __func__);
        return false;
    }
    return true;
}

bool ms_push(int_multiset_t *ms, int value) {
    if (!ms) {
        fprintf(stderr, "<%s>: failed to push: invalid multiset\n", __func__);
        return false;
    }

    int idx = ms_hash(ms->N, value);
    if (!array_push_back(ms->batches[idx].payload_per_batch, value)) {
        fprintf(stderr, "<%s>: failed to push value at batch #%d of multimap\n",
                        __func__, idx+1);
        return false;
    }
    return true;
}

bool ms_finish_push(int_multiset_t *ms) {
    if (!ms) {
        fprintf(stderr, "<%s>: invalid multiset\n", __func__);
        return false;
    }
    if (!ms_update_occupancy_rate(ms)) {
        fprintf(stderr, "<%s>: failed to finialize pushing at %p: "
                        "failed to calc occupancy rate for multimap before extending ! "
                        "All memory was freed\n", __func__, ms);
        return false;
    }
    if (!ms_extend(ms)) {
        fprintf(stderr, "<%s>: failed to finialize pushing at %p\n", __func__, ms);
        return false;
    }
    return true;
}

bool ms_start_erase(int_multiset_t *ms) {
    if (!ms) {
        fprintf(stderr, "<%s>: invalid multiset\n", __func__);
        return false;
    }
    return true;
}

bool ms_erase(int_multiset_t *ms, int value) {
    if (!ms) {
        fprintf(stderr, "<%s>: failed to erase: invalid multiset\n", __func__);
        return false;
    }

    int idx = ms_hash(ms->N, value);
    bool rc = array_erase_value(ms->batches[idx].payload_per_batch, value);
    if (!rc) {
        fprintf(stderr, "<%s>: %d doesn't exists\n", __func__, value);
    }
    return rc;
}

bool ms_finish_erase(int_multiset_t *ms) {
    // TODO: compress by memory if multiset hasn't been updated for a long time 
    if (!ms) {
        fprintf(stderr, "<%s>: invalid multiset\n", __func__);
        return false;
    }
    return ms_update_occupancy_rate(ms);
}

void ms_print(int_multiset_t *ms) {
    if (!ms) {
        printf("{ }\n");
        return;
    }
    
    int N = ms->N;
    printf("{\n");
    for (int i = 0; i < N; i++) {
        array_print(ms->batches[i].payload_per_batch);
    }
    printf("}\n");
}

int ms_search_value(int_multiset_t *ms, int sv) {
    if (!ms) {
        fprintf(stderr, "<%s>: invalid multiset\n", __func__);
        return INT32_MIN;
    }

    int idx = ms_hash(ms->N, sv);
    return array_search(ms->batches[idx].payload_per_batch, sv);
}