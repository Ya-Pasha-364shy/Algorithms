#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "linked_list_2.h"

int_linked_list2_t *ll2_init() {
    int_linked_list2_t *ll = (int_linked_list2_t *)calloc(1, sizeof(int_linked_list2_t));
    if (!ll) {
        perror("failed to allocate linked_list: ");
        return NULL;
    }

    ll->sentinel_node = calloc(1, sizeof(int_linked_list_node2_t));
    if (!ll->sentinel_node) {
        perror("failed to allocate sentinel in linked_list: ");
        free(ll);
        return NULL;
    }
    ll->sentinel_node->payload = INT_MAX;
    ll->size = 0;

    return ll;
}

void ll2_destroy(int_linked_list2_t *ll) {
    int_linked_list_node2_t *iterator = ll->sentinel_node->next_node;
    int_linked_list_node2_t *finish_node = ll->sentinel_node;

    while (iterator != finish_node) {
        int_linked_list_node2_t *tmp = iterator;
        iterator = iterator->next_node;
        free(tmp);
    }
    free(iterator);

    free(ll);
}

bool ll2_push_back(int_linked_list2_t *ll, int value) {
    int_linked_list_node2_t *new_node = (int_linked_list_node2_t *)calloc(1, sizeof(int_linked_list_node2_t));
    if (!new_node) {
        perror("failed to push_back new node: ");
        return false;
    }

    new_node->payload = value;
    new_node->next_node = ll->sentinel_node;

    if (ll->size == 0) {
        ll->sentinel_node->next_node = new_node;
        new_node->prev_node = ll->sentinel_node;
    } else {
        ll->last_node->next_node = new_node;
        new_node->prev_node = ll->last_node;
    }
    ll->last_node = new_node;

    ll->size++;
    return true;
}

bool ll2_insert(int_linked_list2_t *ll, size_t index, int value) {
    if (ll->size <= index) {
        return ll2_push_back(ll, value);
    }
    int_linked_list_node2_t *new_node = NULL;
    int_linked_list_node2_t *prev = NULL;
    int_linked_list_node2_t *iterator = ll->sentinel_node->next_node;
    size_t i = 0;

    while (i < index) {
        prev = iterator;
        iterator = iterator->next_node;
        i++;
    }
    if (prev == NULL) {
        prev = ll->sentinel_node;
    }

    new_node = (int_linked_list_node2_t *)calloc(1, sizeof(int_linked_list_node2_t));
    if (!new_node) {
        perror("failed to insert new node: ");
        return false;
    }
    
    new_node->payload = value;
    
    prev->next_node = new_node;
    new_node->prev_node = prev;
    
    new_node->next_node = iterator;
    iterator->prev_node = new_node;

    ll->size++;

    return true;
}

int ll2_pop_back(int_linked_list2_t *ll) {
    if (!ll->size) {
        return INT_MAX;
    }

    int_linked_list_node2_t *ll2_last_node = ll->last_node;
    int rv = ll2_last_node->payload;

    int_linked_list_node2_t *prev = ll->last_node->prev_node;

    if (prev != ll->sentinel_node) {
        ll->last_node = prev;
        ll->last_node->next_node = ll->sentinel_node;
    } else {
        ll->sentinel_node->next_node = NULL;
        ll->last_node = NULL;
    }
    ll->sentinel_node->prev_node = ll->last_node;

    free(ll2_last_node);
    ll->size--;

    return rv;
}

bool ll2_erase_value(int_linked_list2_t *ll, int value_to_erase) {
    if (ll->size == 0) {
        return false;
    }

    int_linked_list_node2_t *prev = NULL;
    int_linked_list_node2_t *iterator = ll->sentinel_node->next_node;
    size_t i = 0;
    
    for (i = 0; i < ll->size-1; i++) {
        if (iterator->payload == value_to_erase) {
            if (prev != NULL) {
                iterator->next_node->prev_node = prev;
                prev->next_node = iterator->next_node;
            } else {
                iterator->next_node->prev_node = ll->sentinel_node;
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
        (void)ll2_pop_back(ll);
    } else {
        return false;
    }
    
    return true;
}

void ll2_erase_value_by_idx(int_linked_list2_t *ll, int index) {
    if (index >= ll->size) {
        return;
    }

    int_linked_list_node2_t *prev = NULL;
    int_linked_list_node2_t *iterator = ll->sentinel_node->next_node;
    size_t i = 0;

    while (i < index) {
        prev = iterator;
        iterator = iterator->next_node;
        i++;
    }
    ll->size--;

    if (prev) {
        iterator->next_node->prev_node = prev;
        prev->next_node = iterator->next_node;
        if (iterator == ll->last_node) {
            ll->last_node = prev;
        }
    } else if (ll->size > 1) {
        iterator->next_node->prev_node = ll->sentinel_node;
        ll->sentinel_node->next_node = iterator->next_node;
    } else {
        ll->last_node = NULL;
        ll->sentinel_node->next_node = NULL;
        ll->sentinel_node->prev_node = NULL;
    }

    free(iterator);
}

void ll2_print(int_linked_list2_t *ll) {
    if (ll->size == 0) {
        printf("[ ]\n");
        return;
    }

    int_linked_list_node2_t *iterator = ll->sentinel_node->next_node;
    printf("[ ");
    for (int i = 0; i < ll->size-1; i++) {
        printf("%d <-> ", iterator->payload);
        iterator = iterator->next_node;
    }
    printf("%d ]\n", ll->last_node->payload);
}

void ll2_sort(int_linked_list2_t **ll) {
    int_linked_list2_t *_ll = *ll;
    if (_ll->size <= 1) {
        return;
    }

    int_linked_list2_t *ll2_new = ll2_init();
    int_linked_list_node2_t *iterator, *prev_iterator,
                            *min, *min_prev;
    if (!ll2_new) return;
    int ll2_size = _ll->size;

    while (ll2_size > 0) {
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
        ll2_size--;

        min->next_node = ll2_new->sentinel_node;
        if (ll2_new->size == 0) {
            ll2_new->sentinel_node->next_node = min;
        } else {
            ll2_new->last_node->next_node = min;
        }
        ll2_new->last_node = min;
        ll2_new->size++;
    }
    free(_ll->sentinel_node);
    free(_ll);

    *ll = ll2_new;
}

int ll2_search_value(int_linked_list2_t *ll, int sv) {
    if (ll->size == 0) {
        return -1;
    }

    int_linked_list_node2_t *iterator = ll->sentinel_node->next_node;    
    size_t i = 0;

    for (; i < ll->size; i++) {
        if (iterator->payload == sv) {
            return i;
        }
        iterator = iterator->next_node;
    }
    return -1;
}