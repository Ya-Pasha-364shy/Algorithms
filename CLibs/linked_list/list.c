#include <time.h>
#include <stdio.h>
#include <malloc.h>

#include "list.h"

static void setToDefaultsNode(list_node_t node) {
  node->next = NULL;
  node->prev = NULL;
  node->payload = 0;
}

// to avoid memory collisions
static bool thisNodeAlreadyExistsByMemory(
  list_node_t node,
  list_t list) {
  list_node_t iterator = list->first_node; 
  for (int i = 0; i < list->length; i++) {
    if (iterator == node)
      return true;

    iterator = iterator->next;
  }
  return false;
}

void listRemove(list_t list) {
  list_node_t cursor_on_end = list->last_node;
  for (int i = list->length; i > 0; i--) {
    list_node_t tmp = cursor_on_end->prev;
    free(cursor_on_end);
    cursor_on_end = tmp;
  }
  free(list);
}

list_t listInit(size_t size) {
  if (!size) {
    return NULL;
  }
  list_t list = malloc(sizeof(list_s));
  if (!list) {
    return NULL;
  }

  list->length = size;

  list->first_node = malloc(sizeof(list_node_s));
  if (!list->first_node) {
    return NULL;
  }

  setToDefaultsNode(list->first_node);
  list_node_t cursor_on_previous = list->first_node;

  for (size_t i = 1; i < size; i++) {
    list_node_t tmp = malloc(sizeof(list_node_s));
    setToDefaultsNode(tmp);

    tmp->prev = cursor_on_previous;
    cursor_on_previous->next = tmp;
    
    cursor_on_previous = tmp;
  }
  list->last_node = cursor_on_previous;
  list->last_node->next = list->first_node;

  return list;
}

void listInsertAtEnd(list_node_t node, list_t list) {
  if (thisNodeAlreadyExistsByMemory(node, list)) {
    return;
  }
  list->length++;

  list->last_node->next = node;
  list->first_node->prev = node;

  node->prev = list->last_node;
  node->next = list->first_node;

  list->last_node = node;
}

void listInsertAtBegin(list_node_t node, list_t list) {
  if (thisNodeAlreadyExistsByMemory(node, list)) {
    return;
  }
  list->length++;

  list->last_node->next = node;
  list->first_node->prev = node;

  node->prev = list->last_node;
  node->next = list->first_node;

  list->first_node = node;
}

void listInsert(size_t idx, list_node_t node, list_t list) {
  if (idx >= list->length) {
    return;
  }
  if (thisNodeAlreadyExistsByMemory(node, list)) {
    return;
  }

  list_node_t cursor_on_current = list->first_node;
  for (size_t i = 1; i < idx; i++) {
    cursor_on_current = cursor_on_current->next;
  }
  if (idx > 1) {
    node->next = cursor_on_current;
    node->prev = cursor_on_current->prev;

    cursor_on_current->prev->next = node;
    cursor_on_current->prev = node;
  } else if (idx == 1) {
    node->next = list->first_node;
    node->prev = list->first_node;

    cursor_on_current->next = node;
    cursor_on_current->prev = node;

    list->last_node = node;
  } else { // idx == 0
    node->next = cursor_on_current;
    node->prev = cursor_on_current;

    cursor_on_current->next = node;
    cursor_on_current->prev = node;

    list->first_node = node;
  }
  list->length++;
}

void listPrint(list_t list) {
  if (!list) {
    return;
  }
  printf("[ ");
  list_node_t iterator = list->first_node;
  for (size_t i = 0; i < list->length; i++) {
    printf("%p: %d; ", iterator, iterator->payload);
    iterator = iterator->next;
  }
  printf(" ]\n");
}

void listReverseByPayloads(list_t list) {
  int tmp = 0;
  size_t gap = 0;

  while (list->length - gap++ != 1) {
    list_node_t current_node = list->first_node;
    for (size_t i = 0; i < list->length - gap; i++) {
      int tmp = current_node->next->payload;
      current_node->next->payload = current_node->payload;
      current_node->payload = tmp;

      current_node = current_node->next;
    }
  }
}

/*
int listBsearch(list_t list, int number) {
  size_t left = 0;
  size_t right = list->length - 1;
  while (left < right) {
    size_t middle = left + (right - left)/2;
    if (list->first_node[middle].payload == number)
      return middle;
    else if (list->nodes[middle].payload < number)
      left = middle + 1;
    else
      right = middle - 1;
  }
  return EXIT_FAILURE;
}
*/

int main(void) {
  size_t len;
  printf("Get lenght of list: "); scanf("%ld", &len);

  list_t lst = listInit(len);
  if (lst == NULL)
    return EXIT_SUCCESS;

  // listPrint(lst);

  list_node_t item0 = calloc(1, sizeof(list_node_s));
  item0->payload = 111;
  listInsertAtBegin(item0, lst);

  // list_node_t item1 = calloc(1, sizeof(list_node_s));
  // item1->payload = 222;
  // listInsertAtEnd(item1, lst);

  // listPrint(lst);

  // list_node_t item2 = calloc(1, sizeof(list_node_s));
  // item2->payload = 333;
  // listInsert(lst->length / 2, item2, lst);

  // listPrint(lst);
  // listReverseByPayloads(lst);
  // listPrint(lst);

  size_t i = 0;
  FOREACH_NODE_FROM_BEGIN(i, lst) {
    printf("%d \n", node->payload);
  }
  printf("\n");

  i = 0;
  FOREACH_NODE_FROM_END(i, lst) {
    printf("%d\n", node->payload);
  }

  listRemove(lst);


  return EXIT_SUCCESS;  
} 