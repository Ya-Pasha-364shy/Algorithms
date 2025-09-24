#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "linked_list.h"

int_linked_list_t *ll_init() {
    int_linked_list_t *ll = (int_linked_list_t *)calloc(1, sizeof(int_linked_list_t));
    if (!ll) {
        perror("failed to allocate linked_list: ");
        return NULL;
    }

    ll->sentinel_node = calloc(1, sizeof(int_linked_list_node_t));
    if (!ll->sentinel_node) {
        perror("failed to allocate sentinel in linked_list: ");
        free(ll);
        return NULL;
    }
    ll->sentinel_node->payload = INT_MAX;
    ll->size = 0;

    return ll;
}

void ll_destroy(int_linked_list_t *ll) {
    int_linked_list_node_t *iterator = ll->sentinel_node->next_node;
    int_linked_list_node_t *finish_node = ll->sentinel_node;

    while (iterator != finish_node) {
        int_linked_list_node_t *tmp = iterator;
        iterator = iterator->next_node;
        free(tmp);
    }
    free(iterator);

    free(ll);
}

bool ll_push_back(int_linked_list_t *ll, int value) {
    int_linked_list_node_t *new_node = (int_linked_list_node_t *)calloc(1, sizeof(int_linked_list_node_t));
    if (!new_node) {
        perror("failed to push_back new node: ");
        return false;
    }

    new_node->payload = value;
    new_node->next_node = ll->sentinel_node;
    if (ll->size == 0) {
        ll->sentinel_node->next_node = new_node;
    } else {
        ll->last_node->next_node = new_node;
    }
    ll->last_node = new_node;

    ll->size++;
    return true;
}

bool ll_insert(int_linked_list_t *ll, size_t index, int value) {
    if (ll->size <= index) {
        return ll_push_back(ll, value);
    }
    int_linked_list_node_t *new_node = NULL;
    int_linked_list_node_t *prev = NULL;
    int_linked_list_node_t *iterator = ll->sentinel_node->next_node;
    size_t i = 0;

    while (i < index) {
        prev = iterator;
        iterator = iterator->next_node;
        i++;
    }
    if (prev == NULL) {
        prev = ll->sentinel_node;
    }

    new_node = (int_linked_list_node_t *)calloc(1, sizeof(int_linked_list_node_t));
    if (!new_node) {
        perror("failed to insert new node: ");
        return false;
    }
    
    new_node->payload = value;
    prev->next_node = new_node;
    new_node->next_node = iterator;

    ll->size++;
    return true;
}

int ll_pop_back(int_linked_list_t *ll) {
    if (!ll->size) {
        return INT_MAX;
    }

    int_linked_list_node_t *ll_last_node = ll->last_node;
    int rv = ll_last_node->payload;

    int_linked_list_node_t *prev = NULL;
    int_linked_list_node_t *iterator = ll->sentinel_node->next_node;
    while (iterator != ll->last_node) {
        prev = iterator;
        iterator = iterator->next_node;
    }

    if (prev != NULL) {
        ll->last_node = prev;
        ll->last_node->next_node = ll->sentinel_node;
    } else {
        ll->sentinel_node->next_node = NULL;
        ll->last_node = NULL;
    }
    free(ll_last_node);

    ll->size--;
    return rv;
}

bool ll_erase_value(int_linked_list_t *ll, int value_to_erase) {
    if (ll->size == 0) {
        return false;
    }

    int_linked_list_node_t *prev = NULL;
    int_linked_list_node_t *iterator = ll->sentinel_node->next_node;
    size_t i = 0;
    
    for (i = 0; i < ll->size-1; i++) {
        if (iterator->payload == value_to_erase) {
            if (prev != NULL) {
                prev->next_node = iterator->next_node;
            } else {
                ll->sentinel_node->next_node = iterator->next_node;
            }
            free(iterator);
            ll->size--;
            return true;
        }
        prev = iterator;
        iterator = iterator->next_node;
    }
    if (iterator->payload == value_to_erase) {
        (void)ll_pop_back(ll);
    } else {
        return false;
    }
    
    return true;
}

void ll_erase_value_by_idx(int_linked_list_t *ll, int index) {
    if (index >= ll->size) {
        return;
    }

    int_linked_list_node_t *prev = NULL;
    int_linked_list_node_t *iterator = ll->sentinel_node->next_node;
    size_t i = 0;

    while (i < index) {
        prev = iterator;
        iterator = iterator->next_node;
        i++;
    }
    ll->size--;

    if (prev) {
        prev->next_node = iterator->next_node;
        if (iterator == ll->last_node) {
            ll->last_node = prev;
        }
    } else if (ll->size) {
        ll->sentinel_node->next_node = iterator->next_node;
    } else {
        ll->last_node = NULL;
        ll->sentinel_node->next_node = NULL;
    }

    free(iterator);
}

void ll_print(int_linked_list_t *ll) {
    if (ll->size == 0) {
        printf("[ ]\n");
        return;
    }

    int_linked_list_node_t *iterator = ll->sentinel_node->next_node;
    printf("[ ");
    for (int i = 0; i < ll->size-1; i++) {
        printf("%d -> ", iterator->payload);
        iterator = iterator->next_node;
    }
    printf("%d ]\n", ll->last_node->payload);
}

void ll_sort(int_linked_list_t **ll) {
    int_linked_list_t *_ll = *ll;
    if (_ll->size <= 1) {
        return;
    }

    int_linked_list_t *ll_new = ll_init();
    int_linked_list_node_t *iterator, *prev_iterator,
                           *min, *min_prev;
    if (!ll_new) return;
    int ll_size = _ll->size;

    while (ll_size > 0) {
        iterator = _ll->sentinel_node->next_node;
        prev_iterator = _ll->sentinel_node;
        min = iterator;
        min_prev = prev_iterator;

        while (iterator != _ll->sentinel_node) {
            if (iterator->payload < min->payload) {
                min = iterator;
                min_prev = prev_iterator;
            }
            prev_iterator = iterator;
            iterator = iterator->next_node;
        }

        min_prev->next_node = min->next_node;
        if (min == _ll->last_node) {
            _ll->last_node = (min_prev == _ll->sentinel_node) ? NULL : min_prev;
        }
        ll_size--;

        min->next_node = ll_new->sentinel_node;
        if (ll_new->size == 0) {
            ll_new->sentinel_node->next_node = min;
        } else {
            ll_new->last_node->next_node = min;
        }
        ll_new->last_node = min;
        ll_new->size++;
    }
    free(_ll->sentinel_node);
    free(_ll);

    *ll = ll_new;
}

int ll_search_value(int_linked_list_t *ll, int sv) {
    if (ll->size == 0) {
        return -1;
    }

    int_linked_list_node_t *iterator = ll->sentinel_node->next_node;    
    size_t i = 0;

    for (; i < ll->size; i++) {
        if (iterator->payload == sv) {
            return i;
        }
        iterator = iterator->next_node;
    }
    return -1;
}