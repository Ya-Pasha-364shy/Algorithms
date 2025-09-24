#include <stdio.h>

#include "queue.h"

int main(void) {
    int_queue_t *queue = queue_init_default();

    queue_push(queue, 1);
    queue_push(queue, 2);
    queue_push(queue, 3);
    queue_push(queue, 4);
    queue_push(queue, 5);
    queue_print(queue);

    queue_pop(queue);
    queue_print(queue);
    queue_insert(queue, 1, 10);
    queue_insert(queue, 2, 20);
    queue_insert(queue, 0, 30);

    queue_print(queue);

    queue_pop(queue);
    queue_pop(queue);

    queue_print(queue);
    queue_insert(queue, 100, 100);

    queue_print(queue);
    queue_insert(queue, 4, 5);

    queue_pop(queue);
    queue_print(queue);

    queue_push(queue, 12);
    queue_insert(queue, 3, 100);

    queue_print(queue);
    while (!queue_is_empty(queue)) {
        queue_pop(queue);
        queue_print(queue);
    }

    queue_destroy(queue);

    return 0;
}