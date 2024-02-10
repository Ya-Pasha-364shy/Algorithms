#ifndef LIST_LIBRARY_H
#define LIST_LIBRARY_H

#include <stdlib.h>
#include <stdbool.h>

/** @brief
 * Список обладает быстрой вставкой
 * и быстрым удалением элементов
 * с начала и с конца - O(1). 
 * 
 * Чтение занимает время O(n),
 * где n - количество элементов списка.
 * Количество итераций по списку = O(n). 
*/

struct list;
struct list_node;

typedef struct list* list_t;
typedef struct list_node* list_node_t;

/* operations with memory */

void listRemove(list_t list);
list_t listInit(size_t lst_size);

void listInsertAtEnd(list_t list, list_node_t node);
void listInsertAtBegin(list_t list, list_node_t node);
void listInsert(list_t list,  list_node_t node, size_t idx);

void listErase(list_t list); 
void listRemoveAllNodes(list_t list);
void listRemoveNodeByIndex(list_t list, size_t index);

/* algorithms for linked list */

void listSort(list_t list);
void listPrint(list_t list);
void listReverseByPayloads(list_t list);
int listBsearch(list_t list, int number);

/* Calls for initialize a two-way list */

list_t List(size_t nmemb);

/* defining of list and list_node by structs */

typedef struct list_node {
  struct list_node* next;
  struct list_node* prev;

  int payload;
} list_node_s;

typedef list_node_s* list_node_t;

typedef struct list {
  size_t length;

  list_node_t last_node;
  list_node_t first_node;

  void (*listRemove)(struct list*);

  void (*listInsertAtEnd)(struct list* list, list_node_t node);
  void (*listInsertAtBegin)(struct list* list, list_node_t node);
  void (*listInsert)(struct list* list, list_node_t node, size_t idx);

  void (*listSort)(struct list* list);
  void (*listErase)(struct list* list);
} list_s;

typedef list_s* list_t;

/* Macroses foreach */

#define FOREACH_NODE_FROM_END(i, list) \
  i = 0; \
  for (list_node_t node = list->last_node; \
    i < list->length; \
    ++i, node = node->prev)

#define FOREACH_NODE_FROM_END_WITHOUT_TRANSITION(i, list) \
  i = list->length; \
  for (list_node_t node = list->last_node; \
       i > 0; --i)

#define FOREACH_NODE_FROM_BEGIN(i, list) \
  i = 0; \
  for (list_node_t node = list->first_node; \
    i < list->length; \
    ++i, node = node->next)

#endif // LIST_LIBRARY_H