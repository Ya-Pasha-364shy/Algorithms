#include "list.h"

/* static functions are "trusted" */

static void setToDefaultsNode(list_node_t node) {
  node->next = NULL;
  node->prev = NULL;
  node->payload = 0;
}

// to avoid memory collisions
static bool thisNodeAlreadyExistsByMemory(list_node_t node, list_t list) {
  list_node_t iterator = list->first_node; 
  for (int i = 0; i < list->length; i++) {
    if (iterator == node) {
      return true;
    }
    iterator = iterator->next;
  }
  return false;
}

static list_node_t getNodeByIndex(list_t list, size_t index) {
  size_t iterator;
  FOREACH_NODE_FROM_BEGIN(iterator, list) {
    if (iterator == index) {
      return node;
    }
  }
  return NULL;
}

static list_node_t createCopyOfNode(list_node_t source_node) {
  list_node_t destination_node = calloc(1, sizeof(list_node_s));
  if (!destination_node) {
    return NULL;
  }
  destination_node->payload = source_node->payload;
  return destination_node;
}

static list_t createCopyOfListByMoving(list_t source_list) {
  size_t iterator;
  list_t copy_list = List(0, false);

  FOREACH_NODE_FROM_BEGIN(iterator, source_list) {
    list_node_t copyed_node = createCopyOfNode(node);
    copy_list->listInsertAtEnd(copy_list, copyed_node);
  }
  source_list->listRemove(source_list);

  return copy_list;
}

static bool lessOrEqualThanPivot(const list_node_t pivot_obj,
                                 const list_node_t current_obj) {
  return current_obj->payload <= pivot_obj->payload; 
}

static bool greaterThanPivot(const list_node_t pivot_obj,
                             const list_node_t current_obj) {
  return current_obj->payload > pivot_obj->payload;
}

typedef bool (*comparatorWithPivot)(list_node_t, list_node_t);

static list_t createListByCondition(const list_t list, list_node_t pivot_node,
                                    comparatorWithPivot cmp) {
  size_t iterator;
  list_t selected_list = List(0, false);

  if (cmp == lessOrEqualThanPivot) {
    unsigned int pivot_duplicates = 0;

    FOREACH_NODE_FROM_BEGIN(iterator, list) {  
      if (node->payload == pivot_node->payload) {
        ++pivot_duplicates;
      }
    }
    FOREACH_NODE_FROM_BEGIN(iterator, list) {
      if (cmp(pivot_node, node)) {
        if (pivot_node->payload == node->payload && (--pivot_duplicates == 0)) {
            continue;
        }
        list_node_t copyed_node = createCopyOfNode(node);
        selected_list->listInsertAtEnd(selected_list, copyed_node);
      }
    }
  } else if (cmp == greaterThanPivot) {
    FOREACH_NODE_FROM_BEGIN(iterator, list) {
      if (cmp(pivot_node, node)) {
        list_node_t copyed_node = createCopyOfNode(node);
        selected_list->listInsertAtEnd(selected_list, copyed_node);
      }
    }
  }
  if (selected_list->length == 0) {
    free(selected_list);
    return NULL;
  }
  return selected_list;
}

static list_t mergeLists(list_t less_than_pivot_list,
                         list_node_t pivot_node,
                         list_t greater_than_pivot_list) {
  if (less_than_pivot_list != NULL &&
      greater_than_pivot_list != NULL) {
    // prepare pivot_node
    pivot_node->prev = less_than_pivot_list->last_node;
    pivot_node->next = greater_than_pivot_list->first_node;
    // change pointers on "base pivot_list"
    less_than_pivot_list->last_node->next = pivot_node;
    less_than_pivot_list->last_node = pivot_node;
    // binding another list to "base list" (already with pivot)
    greater_than_pivot_list->first_node->prev = less_than_pivot_list->last_node;
    greater_than_pivot_list->last_node->next = less_than_pivot_list->first_node;
    less_than_pivot_list->first_node->prev = greater_than_pivot_list->last_node;

    /* "+1" -- it's "pivot" element */
    less_than_pivot_list->length += greater_than_pivot_list->length + 1;

    return createCopyOfListByMoving(less_than_pivot_list);
  } else if (less_than_pivot_list != NULL &&
             greater_than_pivot_list == NULL) {
    // prepare pivot_node
    pivot_node->prev = less_than_pivot_list->last_node;
    pivot_node->next = less_than_pivot_list->first_node;
    // change pointers on "base pivot_list"
    less_than_pivot_list->last_node->next = pivot_node;
    less_than_pivot_list->last_node = pivot_node;
    less_than_pivot_list->first_node->prev = pivot_node;

    less_than_pivot_list->length++;

    return createCopyOfListByMoving(less_than_pivot_list);
  } else if (less_than_pivot_list == NULL &&
             greater_than_pivot_list != NULL) {
    // prepare pivot node
    pivot_node->prev = greater_than_pivot_list->last_node;
    pivot_node->next = greater_than_pivot_list->first_node;
    // change pointers on "base pivot list"
    greater_than_pivot_list->first_node->prev = pivot_node;
    greater_than_pivot_list->first_node = pivot_node;
    greater_than_pivot_list->last_node->next = pivot_node;

    greater_than_pivot_list->length++;

    return createCopyOfListByMoving(greater_than_pivot_list);
  } else {
    // an impossible case if called recursively
    // from the listSort function.
    // However, let’s handle it just in case.
    return NULL;
  }
}

void listRemove(list_t list) {
  if (LIKE(list == NULL)) {
    return;
  }

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

list_t listInit(size_t size, bool make_random_values) {
  list_t list = calloc(1, sizeof(list_s));
  if (!list) {
    return NULL;
  }
  list->length = size;
  if (LIKE(size == 0)) {
    return list;
  }

  list->first_node = malloc(sizeof(list_node_s));
  if (!list->first_node) {
    return NULL;
  }

  setToDefaultsNode(list->first_node);  
  srand(time(NULL));
  if (make_random_values) {
    list->first_node->payload = rand() % 100;
  } else {
    list->first_node->payload = 0;
  }

  list_node_t cursor_on_previous = list->first_node;

  for (size_t i = 1; i < size; i++) {
    list_node_t tmp = malloc(sizeof(list_node_s));
    setToDefaultsNode(tmp);

    tmp->prev = cursor_on_previous;
    if (make_random_values) {
      tmp->payload = rand() % 100;  
    } else {
      tmp->payload = 0;
    }
    cursor_on_previous->next = tmp;
    cursor_on_previous = tmp;
  }
  list->last_node = cursor_on_previous;
  list->last_node->next = list->first_node;

  return list;
}

void listInsertAtEnd(list_t list, list_node_t node) {
  if (LIKE(node == NULL) || LIKE(list == NULL)) {
    return;
  }
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

void listInsertAtBegin(list_t list, list_node_t node) {
  if (LIKE(list == NULL) || LIKE(node == NULL)) {
    return;
  }
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

void listInsert(list_t list, list_node_t node, size_t idx) {
  if (LIKE(list == NULL) || LIKE(node == NULL)) {
    return;
  }
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
  if (LIKE(list == NULL) || LIKE(index >= list->length)) {
    return;
  } else if (index == 0) {
    return listRemoveNodeFromBegin(list);
  } else if (index == list->length - 1) {
    return listRemoveNodeFromEnd(list);
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
  list->length--;
  free(node_to_remove);
}

void listRemoveNodeFromEnd(list_t list) {
  if (list == NULL) {
    return;
  }
  list_node_t node_to_remove = list->last_node;
  node_to_remove->prev->next = list->first_node;
  list->first_node->prev = node_to_remove->prev;
  list->last_node = node_to_remove->prev;
  list->length--;
  free(node_to_remove);

}

void listRemoveNodeFromBegin(list_t list) {
  if (list == NULL) {
    return;
  }
  list_node_t node_to_remove = list->first_node;
  node_to_remove->next->prev = list->last_node;
  list->last_node->next = node_to_remove->next;
  list->first_node = node_to_remove->next;
  list->length--;
  free(node_to_remove);
}

/* algorithms for linked list */

void listPrint(const char* name, list_t list) {
  if (LIKE(list == NULL) || LIKE(name == NULL)) {
    return;
  }
  printf("%s = [ ", name);
  list_node_t iterator = list->first_node;
  for (size_t i = 0; i < list->length; i++) {
    printf(" %d ", iterator->payload);
    iterator = iterator->next;
  }
  printf(" ]\n");
}

list_t listSort(list_t list) {
  if (LIKE(list == NULL)) {
    return NULL;
  }
  if (LIKE(list->length == 1)) {
    return list;
  }

  // TODO(K1rch): change O(n^2) on simple O(n)
  list_node_t pivot_node =
                  getNodeByIndex(list, list->length / 2);
  list_t greater_pivot = createListByCondition(list, pivot_node,
                                               &greaterThanPivot);
  list_t less_pivot = createListByCondition(list, pivot_node,
                                            &lessOrEqualThanPivot);
  // O(log(n)), но если на каждой итерации будет выбираться самый бОльший
  // или самый меньший pivot, то тогда будет O(n)
  return mergeLists(listSort(less_pivot), pivot_node, listSort(greater_pivot));
}

void listReverseByPayloads(list_t list) {
  if (LIKE(list == NULL)) {
    return;
  }
  
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
int listBsearch(list_t list, int payload) {
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

list_t List(size_t nmemb, bool make_random_values) {
  list_t this = listInit(nmemb, make_random_values);

  this->listRemove = &listRemove;

  this->listInsert = &listInsert;
  this->listInsertAtEnd = &listInsertAtEnd;
  this->listInsertAtBegin = &listInsertAtBegin;

  // this->listSort = &listSort;
  this->listErase = &listErase;

  return this;
}

/* Some helpful methods */

list_t init(int8_t nmemb, ...) {
  list_t list = List(0, false);
  va_list args;
  va_start(args, nmemb);
  for (unsigned i = 0; i < nmemb; i++) {
    list_node_t node = calloc(1, sizeof(list_node_s));
    node->payload = va_arg(args, unsigned int);
    list->listInsertAtEnd(list, node);
  }
  va_end(args);

  return list;
}

int findIndexByElement(list_t list, list_node_t desired_node) {
  int index = -1;
  if (LIKE(list == NULL) || LIKE(desired_node == NULL)) {
    return index;
  }

  size_t iterator;
  FOREACH_NODE_FROM_BEGIN(iterator, list) {
    if (node == desired_node ||
        node->payload == desired_node->payload) {
      index = iterator;
      break;
    }
  }

  return index;
}

list_node_t findElementByIndex(list_t list, size_t desired_node_index) {
  list_node_t required_node = NULL;
  if (LIKE(list == NULL) || LIKE(desired_node_index >= list->length)) {
    return required_node;
  }

  return getNodeByIndex(list, desired_node_index);
}