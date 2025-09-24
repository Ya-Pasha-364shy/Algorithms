#include "array.h"

#include <stdio.h>

int_array_t *array_init(size_t N) {
    int_array_t *array = (int_array_t *)calloc(1, sizeof(int_array_t));
    if (!array) {
        perror("array_init: calloc failed: ");
        return NULL;
    } 
    if (!N) { 
        N = 1;
    }
    array->N = N;
    array->payload = (int *)calloc(N, sizeof(int));
    if (!array->payload) {
        free(array);
        perror("array_init: calloc failed: ");
        return NULL;
    }

    return array;
}

int_array_t *array_init_default() {
    return array_init(0);
}

void array_destroy(int_array_t *array) {
    if (array) {
        free(array->payload);
    }
    free(array);
    array = NULL;
}

static bool array_extend(int_array_t *array) {
    if (!array || !array->payload) {
        fprintf(stderr, "<%s>: array or payload is NULL\n", __func__);
        return false;
    }

    if (array->M < array->N) {
        return true;
    }
    int *a_payload = array->payload;
    size_t new_N = array->N*2;

    a_payload = (int *)realloc(a_payload, new_N * sizeof(int));
    if (a_payload == NULL) {
        perror("array_extend: realloc failed: ");
        return false;
    }
    array->payload = a_payload;
    array->N = new_N;

    return true;
}

bool array_push_back(int_array_t *array, int value) {    
    if (!array || !array->payload) {
        fprintf(stderr, "<%s>: array or payload is NULL\n", __func__);
        return false;
    }

    if (array->M == array->N) {
        if (!array_extend(array)) {
            fprintf(stderr, "array_push_back: failed to push %d\n", value);
            return false;
        }
    }
    array->payload[array->M] = value;
    array->M++;
    array->is_sorted = false;

    return true;
}

bool array_insert(int_array_t *array, size_t index, int value) {
    if (!array || !array->payload) {
        fprintf(stderr, "<%s>: array or payload is NULL\n", __func__);
        return false;
    }

    if (array->M == array->N) {
        if (!array_extend(array)) {
            fprintf(stderr, "array_insert: failed to insert at index %ld\n", index);
            return false;
        }
    }
    if (array->M <= index) {
        return array_push_back(array, value);
    }

    int *a_payload = array->payload;

    size_t idx = array->M;
    for (; idx > index; idx--) {
        a_payload[idx] = a_payload[idx-1];
    }
    a_payload[idx] = value;
    array->M++;
    array->is_sorted = false;

    return true;
}

int array_pop_back(int_array_t *array) {
    if (!array || !array->payload) {
        fprintf(stderr, "<%s>: array or payload is NULL\n", __func__);
        return __INT_MAX__;
    }

    if (array->M > 0) {
        int rv = array->payload[array->M-1];
        array->payload[array->M-1] = 0;
        array->M--;
  
        return rv;
    }
    return __INT_MAX__;
}

bool array_erase_value(int_array_t *array, int value_to_erase) {
    if (!array || !array->payload) {
        fprintf(stderr, "<%s>: array or payload is NULL\n", __func__);
        return false;
    }
    size_t i = 0;

    for (; i < array->M; i++) {
        if (array->payload[i] == value_to_erase) {
            i++;
            for (; i < array->M; i++) {
                array->payload[i-1] = array->payload[i];
            }
            array->payload[i-1] = 0;
            array->M--;

            return true;
        }
    }
    return false;
}

void array_erase_value_by_idx(int_array_t *array, size_t index) {
    if (!array || !array->payload) {
        fprintf(stderr, "<%s>: array or payload is NULL\n", __func__);
        return;
    }

    if (!array->M || index >= array->M) {
        return;
    }
    if (index == array->M-1) {
        (void)array_pop_back(array);
        return;
    }

    size_t i = index + 1;
    for (; i < array->M; i++) {
        array->payload[i-1] = array->payload[i];
    }
    array->payload[i - 1] = 0;
    array->M--;
}

void array_print(int_array_t *array) {
    if (!array || !array->payload) {
        fprintf(stderr, "<%s>: array or payload is NULL\n", __func__);
        return;
    }

    int i = 0;
    if (!array->M) {
        printf("[ ]\n");
        return;
    }

    printf("[ ");
    for (; i < array->M-1; i++) {
        printf("%d, ", array->payload[i]);
    }
    printf("%d ]\n", array->payload[i]);
}

static void _array_sort(int *array, int l, int r) {
    if (l >= r) return;
    
    int i = l;
    int j = r;
    int pivot = array[(i + j)/2];

    while (i <= j) {
        while (array[i] < pivot) i++;
        while (array[j] > pivot) j--;

        if (i <= j) {
            int tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;

            i++;
            j--;
        }
    }

    if (l < j) _array_sort(array, l, j);
    if (r > i) _array_sort(array, i, r);
}

void array_sort(int_array_t *array) {
    if (!array) {
        fprintf(stderr, "<%s>: array or payload is NULL\n", __func__);
        return;
    }

    _array_sort(array->payload, 0, array->M-1);
    array->is_sorted = true;
}

bool array_bin_search(int_array_t *array, int s_v) {
    if (!array) {
        fprintf(stderr, "<%s>: array or payload is NULL\n", __func__);
        return false;
    }

    int left = 0;
    int right = array->M-1;

    while (left <= right) {
        int mid_idx = (right - left)/2 + left;
        int c_v = array->payload[mid_idx];

        if (s_v > c_v) {
            left = mid_idx + 1;
        } else if (s_v < c_v) {
            right = mid_idx - 1;
        } else {
            return true;
        }
    }

    return false;
}

bool array_search(int_array_t *array, int s_v) {
    if (!array) {
        fprintf(stderr, "<%s>: array or payload is NULL\n", __func__);
        return false;
    }

    if (!array->is_sorted) {
        for (size_t i = 0; i < array->M; i++) {
            if (array->payload[i] == s_v) return true;
        }
    } else {
        return array_bin_search(array, s_v);
    }
    return false;
}