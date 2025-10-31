#ifndef _QUEUE_HEADER_H_
#define _QUEUE_HEADER_H_

#include <stdbool.h>

typedef struct int_queue_s {
    int *payload;

    size_t N; // capacity
    size_t head_idx; // front of queue (front value stored here)
    size_t tail_idx; // back of queue (next free idx)
} int_queue_t;

int_queue_t *queue_init(size_t N);

int_queue_t *queue_init_default();

void queue_destroy(int_queue_t *queue);

bool queue_push(int_queue_t *queue, int value);

void queue_pop(int_queue_t *queue);

int *queue_front(int_queue_t *queue);

bool queue_insert(int_queue_t *queue, size_t index, int value);

void queue_print(int_queue_t *queue);

bool queue_is_empty(int_queue_t *queue);

#endif // _QUEUE_HEADER_H_