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

static list_node_t getNodeByIndex(list_t list, size_t index) {
  size_t i = 0;
  FOREACH_NODE_FROM_BEGIN(i, list) {
    if (i == index) {
      return node;
    }
  }
  return NULL;
}

static bool lessThanPivot(list_node_t pivot_obj, list_node_t current_obj) {
  return current_obj->payload < pivot_obj->payload; 
}

static bool greaterThanPivot(list_node_t pivot_obj, list_node_t current_obj) {
  return current_obj->payload > pivot_obj->payload;
}

typedef bool (*comparatorWithPivot)(list_node_t, list_node_t);

static list_t createListByCondition(list_t list, list_node_t pivot_node,
                                    comparatorWithPivot cmp) {
  size_t iterator;
  list_t selected_list = listInit(0);
  FOREACH_NODE_FROM_BEGIN(iterator, list) {
    if (cmp(pivot_node, node)) {
      selected_list->listInsertAtEnd(selected_list, node);
    }
  }
  if (selected_list->length == 0) {
    free(selected_list);
    return NULL;
  }
}

void listRemove(list_t list) {
  size_t iterator;
  list_node_t tmp_cursor;
  FOREACH_NODE_FROM_END_WITHOUT_TRANSITION(iterator, list) {
    tmp_cursor = node->prev;
    free(node);
    // manual transition
    node = tmp_cursor;
  }
  list->last_node = NULL;
  list->first_node = NULL;

  free(list);
}

list_t listInit(size_t size) {
  list_t list = malloc(sizeof(list_s));
  if (!list) {
    return NULL;
  }
  if (!size) {
    list->length = 0;
    list->last_node = NULL;
    list->first_node = NULL;
    return list;
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

void listInsertAtEnd(list_t list, list_node_t node) {
  if (thisNodeAlreadyExistsByMemory(node, list)) {
    return;
  }
  list->length++;
  if (list->last_node == NULL && list->first_node == NULL) {
    list->last_node = node;
    list->first_node = node;
    
    list->first_node->next = list->last_node;
    list->first_node->prev = list->last_node;

    list->last_node->prev = list->first_node;
    list->last_node->next = list->first_node;
  } else {
    list->last_node->next = node;
    list->first_node->prev = node;

    node->prev = list->last_node;
    node->next = list->first_node;

    list->last_node = node;
  }
}

void listInsertAtBegin(list_t list, list_node_t node)  {
  if (thisNodeAlreadyExistsByMemory(node, list)) {
    return;
  }
  list->length++;
  if (list->last_node == NULL && list->first_node == NULL) {
    list->last_node = node;
    list->first_node = node;
    
    list->first_node->next = list->last_node;
    list->first_node->prev = list->last_node;

    list->last_node->prev = list->first_node;
    list->last_node->next = list->first_node;
  } else {
    list->last_node->next = node;
    list->first_node->prev = node;

    node->prev = list->last_node;
    node->next = list->first_node;

    list->first_node = node;
  }
}

void listInsert(list_t list,  list_node_t node, size_t idx) {
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

void listErase(list_t list) {
  size_t iterator;
  FOREACH_NODE_FROM_BEGIN(iterator, list) {
    node->payload = 0;
  }
}

void listRemoveAllNodes(list_t list) {
  size_t iterator;
  list_node_t tmp_cursor;
  FOREACH_NODE_FROM_END_WITHOUT_TRANSITION(iterator, list) {
    tmp_cursor = node->prev;
    free(node);
    // manual transition
    node = tmp_cursor;
  }
  list->last_node = NULL;
  list->first_node = NULL;
}

void listRemoveNodeByIndex(list_t list, size_t index) {
  if (index >= list->length) {
    return;
  }

  size_t iterator; 
  list_node_t node_to_remove = NULL;
  FOREACH_NODE_FROM_BEGIN(iterator, list) {
    if (iterator == index) {
      node_to_remove = node;
      break;
    }
  }
  if (node_to_remove == NULL) {
    return;
  }
  node_to_remove->prev->next = node_to_remove->next;
  node_to_remove->next->prev = node_to_remove->prev;
  free(node_to_remove);
}

/* algorithms for linked list */

void listSort(list_t list) {
  list_node_t pivot_node = getNodeByIndex(list, list->length / 2);
  list_t less_pivot = createListByCondition(list, pivot_node,
                                            &lessThanPivot);
  list_t greater_pivot = createListByCondition(list, pivot_node,
                                               &greaterThanPivot);
  // TODO(k1rch): merge lists with free(less_pivot) or listSort(greater_pivot)
  //              depending on lenght of lists. Удалить сами списки, а элементы
  //              элегантно перенести в новый список. Это можно сделать за O(1)
  // return mergeLists(listSort(less_pivot), pivot_node, listSort(greater_pivot));
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

list_t List(size_t nmemb) {
  list_t this = listInit(nmemb);

  this->listRemove = &listRemove;

  this->listInsert = &listInsert;
  this->listInsertAtEnd = &listInsertAtEnd;
  this->listInsertAtBegin = &listInsertAtBegin;

  // this->listSort = &listSort;
  // this->listErase = &listErase;

  return this;
}

int main(void) {
  size_t nmemb;
  printf("Get lenght of list: "); scanf("%ld", &nmemb);

  list_t lst = List(nmemb);

  if (lst == NULL)
    return EXIT_SUCCESS;

  // listPrint(lst);

  list_node_t item0 = calloc(1, sizeof(list_node_s));
  item0->payload = 111;
  lst->listInsertAtBegin(lst, item0);

  list_node_t item1 = calloc(1, sizeof(list_node_s));
  item1->payload = 222;
  lst->listInsertAtEnd(lst, item1);

  // listPrint(lst);

  list_node_t item2 = calloc(1, sizeof(list_node_s));
  item2->payload = 333;
  listInsert(lst, item2, lst->length / 2);

  listPrint(lst);
  listReverseByPayloads(lst);
  // listPrint(lst);

  size_t i;
  FOREACH_NODE_FROM_BEGIN(i, lst) {
    printf("%d \n", node->payload);
  }

  lst->listRemove(lst);

  return EXIT_SUCCESS;  
} 