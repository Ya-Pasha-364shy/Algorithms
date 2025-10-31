#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#include "deque.h"

int_deq_t *deq_init() {
    int_deq_t *deq = (int_deq_t *)calloc(1, sizeof(int_deq_t));
    if (!deq) {
        perror("failed to allocate deque: ");
        return NULL;
    }

    deq->sentinel_node = calloc(1, sizeof(int_deq_node_t));
    if (!deq->sentinel_node) {
        perror("failed to allocate sentinel in deque: ");
        free(deq);
        return NULL;
    }
    deq->sentinel_node->payload = INT_MAX;
    deq->size = 0;

    return deq;
}

void deq_destroy(int_deq_t *deq) {
    int_deq_node_t *iterator = deq->sentinel_node->next_node;
    int_deq_node_t *finish_node = deq->sentinel_node;

    while (iterator != finish_node) {
        int_deq_node_t *tmp = iterator;
        iterator = iterator->next_node;
        free(tmp);
    }
    free(iterator);

    free(deq);
}

bool deq_push_back(int_deq_t *deq, int value) {
    int_deq_node_t *new_node = (int_deq_node_t *)calloc(1, sizeof(int_deq_node_t));
    if (!new_node) {
        perror("failed to push_back new node: ");
        return false;
    }

    new_node->payload = value;
    new_node->next_node = deq->sentinel_node;

    if (deq->size == 0) {
        deq->sentinel_node->next_node = new_node;
        new_node->prev_node = deq->sentinel_node;
    } else {
        deq->last_node->next_node = new_node;
        new_node->prev_node = deq->last_node;
    }
    deq->last_node = new_node;

    deq->size++;
    return true;
}

bool deq_push_front(int_deq_t *deq, int value) {
    int_deq_node_t *new_node = (int_deq_node_t *)calloc(1, sizeof(int_deq_node_t));
    if (!new_node) {
        perror("failed to push_front new node: ");
        return false;
    }

    new_node->payload = value;
    new_node->prev_node = deq->sentinel_node;

    if (deq->size == 0) {
        new_node->next_node = deq->sentinel_node;
        deq->sentinel_node->prev_node = new_node;
        deq->last_node = new_node;
    } else {
        new_node->next_node = deq->sentinel_node->next_node;
        deq->sentinel_node->next_node->prev_node = new_node; 
    }
    deq->sentinel_node->next_node = new_node;

    deq->size++;
    return true;
}

int deq_pop_back(int_deq_t *deq) {
    if (!deq->size) {
        return INT_MAX;
    }

    int_deq_node_t *deq_last_node = deq->last_node,
                   *prev = NULL;
    int rv = deq_last_node->payload;

    prev = deq->last_node->prev_node;
    if (prev != deq->sentinel_node) {
        deq->last_node = prev;
        deq->last_node->next_node = deq->sentinel_node;
    } else {
        deq->sentinel_node->next_node = NULL;
        deq->last_node = NULL;
    }
    deq->sentinel_node->prev_node = deq->last_node;

    free(deq_last_node);
    deq->size--;

    return rv;
}

int deq_pop_front(int_deq_t *deq) {
    if (!deq->size) {
        return INT_MAX;
    }

    int_deq_node_t *deq_fst_node = deq->sentinel_node->next_node,
                   *next = NULL;
    int rv = 0;

    if (deq_fst_node) {
        next = deq_fst_node->next_node;
    } else {
        fprintf(stderr, "deq_pop_front failed\n");
        return INT_MAX;
    }

    if (deq_fst_node != deq->sentinel_node) {
        rv = deq_fst_node->payload;
        if (next != deq->sentinel_node) {
            deq->sentinel_node->next_node = next;
            next->prev_node = deq->sentinel_node; 
        } else {
            // size == 1
            deq->sentinel_node->next_node = NULL;
            deq->sentinel_node->prev_node = NULL;
            deq->last_node = NULL;
        }
        free(deq_fst_node);
    } else {
        // size == 0  - reached unreachable
        return INT_MAX;
    }

    deq->size--;
    return rv;
}

void deq_print(int_deq_t *deq) {
    if (deq->size == 0) {
        printf("[ ]\n");
        return;
    }

    int_deq_node_t *iterator = deq->sentinel_node->next_node;
    printf("[ ");
    for (int i = 0; i < deq->size-1; i++) {
        printf("%d <-> ", iterator->payload);
        iterator = iterator->next_node;
    }
    printf("%d ]\n", deq->last_node->payload);
}

void deq_sort(int_deq_t **deq) {
    int_deq_t *_deq = *deq;
    if (_deq->size <= 1) {
        return;
    }

    int_deq_t *deq_new = deq_init();
    int_deq_node_t *iterator, *prev_iterator,
                              *min, *min_prev;
    if (!deq_new) return;
    int deq_size = _deq->size;

    while (deq_size > 0) {
        iterator = _deq->sentinel_node->next_node->next_node;
        prev_iterator = _deq->sentinel_node->next_node;
        min = prev_iterator;
        min_prev = _deq->sentinel_node;

        while (iterator != _deq->sentinel_node) {
            if (iterator->payload < min->payload) {
                min = iterator;
                min_prev = prev_iterator;
            }
            prev_iterator = iterator;
            iterator = iterator->next_node;
        }

        min_prev->next_node = min->next_node;
        if (min == _deq->last_node) {
            _deq->last_node = (min_prev == _deq->sentinel_node) ? NULL : min_prev;
        }
        deq_size--;

        min->next_node = deq_new->sentinel_node;
        if (deq_new->size == 0) {
            deq_new->sentinel_node->next_node = min;
            min->prev_node = deq_new->sentinel_node;
        } else {
            deq_new->last_node->next_node = min;
            min->prev_node = deq_new->last_node;
        }
        deq_new->last_node = min;
        deq_new->size++;
    }
    free(_deq->sentinel_node);
    free(_deq);

    *deq = deq_new;
}

int deq_search_value(int_deq_t *deq, int sv) {
    if (deq->size == 0) {
        return -1;
    }

    int_deq_node_t *iterator = deq->sentinel_node->next_node;    
    size_t i = 0;

    for (; i < deq->size; i++) {
        if (iterator->payload == sv) {
            return i;
        }
        iterator = iterator->next_node;
    }
    return -1;
}