#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "queue.h"

int_queue_t *queue_init(size_t N) {
    int_queue_t *queue = (int_queue_t *)calloc(1, sizeof(int_queue_t));
    if (!queue) {
        fprintf(stderr, "<%s>: calloc failed: %s\n", __func__, strerror(errno));
        return NULL;
    }
    if (!N) {
        N = 1;
    } 
    queue->N = N;
    queue->payload = (int *)calloc(N, sizeof(int));
    if (!queue->payload) {
        free(queue);
        fprintf(stderr, "<%s:%d>: calloc failed: %s\n", __func__, __LINE__, strerror(errno));
        return NULL;
    }

    return queue;
}

int_queue_t *queue_init_default() {
    return queue_init(0);
}

void queue_destroy(int_queue_t *queue) {
    if (queue) {
        free(queue->payload);
        queue->payload = NULL;
    }
    free(queue);
    queue = NULL;
}

static bool queue_extend(int_queue_t *queue) {
    size_t old_N = queue->N;
    size_t new_N = old_N * 2;
    int *new_payload = calloc(new_N, sizeof(int));
    if (!new_payload) {
        fprintf(stderr, "<%s>: calloc failed: %s\n", __func__, strerror(errno));
        return false;
    }

    size_t j = 0;
    for (size_t i = queue->head_idx; i != queue->tail_idx; i = (i + 1) % old_N) {
        new_payload[j++] = queue->payload[i];
    }

    free(queue->payload);
    queue->payload = new_payload;
    queue->N = new_N;
    queue->head_idx = 0;
    queue->tail_idx = j;

    return true;
}

bool queue_push(int_queue_t *queue, int value) {
    if (!queue || !queue->payload) {
        fprintf(stderr, "<%s>: queue of payload is NULL\n", __func__);
        return false;
    }

    size_t next_tail = (queue->tail_idx + 1) % queue->N;
    if (next_tail == queue->head_idx) {
        // this adding must extend queue, coz it's action full fills queue.
        if (!queue_extend(queue)) {
            fprintf(stderr, "<%s>: failed to extend. Queue unchanged\n", __func__);
            return false;
        }
        next_tail = (queue->tail_idx + 1) % queue->N;
    }

    queue->payload[queue->tail_idx] = value;
    queue->tail_idx = next_tail;
    return true;
}

void queue_pop(int_queue_t *queue) {
    if (!queue || !queue->payload) {
        fprintf(stderr, "<%s>: queue of payload is NULL\n", __func__);
        return;
    }
    if (queue->head_idx == queue->tail_idx) {
        return; // empty
    }
    queue->head_idx = (queue->head_idx + 1) % queue->N;
}

int *queue_front(int_queue_t *queue) {
    if (!queue || !queue->payload) {
        fprintf(stderr, "<%s>: queue of payload is NULL\n", __func__);
        return NULL;
    }
    if (queue->tail_idx == queue->head_idx) {
        return NULL; // empty
    }
    return &queue->payload[queue->head_idx];
}

bool queue_insert(int_queue_t *queue, size_t index, int value) {
    if (!queue || !queue->payload) {
        fprintf(stderr, "<%s>: queue of payload is NULL\n", __func__);
        return false;
    }

    size_t next_tail, real_index, i;
    size_t size = (queue->tail_idx + queue->N - queue->head_idx) % queue->N;
    if (index > size) {
        return queue_push(queue, value);
    }

    next_tail = (queue->tail_idx + 1) % queue->N;
    if (next_tail == queue->head_idx) {
        if (!queue_extend(queue)) {
            fprintf(stderr, "<%s>: failed to extend. Queue unchanged\n", __func__);
            return false;
        }
        size = (queue->tail_idx + queue->N - queue->head_idx) % queue->N;
    }

    real_index = (queue->head_idx + index) % queue->N;
    i = queue->tail_idx;
    while (i != real_index) {
        size_t prev = (i + queue->N - 1) % queue->N;
        queue->payload[i] = queue->payload[prev];
        i = prev;
    }

    queue->payload[real_index] = value;
    queue->tail_idx = (queue->tail_idx + 1) % queue->N;

    return true;
}

void queue_print(int_queue_t *queue) {
    printf("[");
    if (!queue || !queue->payload || queue->head_idx == queue->tail_idx) {
        printf(" ]\n");
        return;
    }

    for (size_t i = queue->head_idx; i != queue->tail_idx; i = (i + 1) % queue->N) {
        printf("%d", queue->payload[i]);
        size_t next = (i + 1) % queue->N;
        if (next != queue->tail_idx) printf(", ");
    }
    printf("]\n");
}

bool queue_is_empty(int_queue_t *queue) {
    return queue->head_idx == queue->tail_idx;
}