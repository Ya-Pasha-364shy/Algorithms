#ifndef LIST_LIBRARY_H
#define LIST_LIBRARY_H

#include <stdlib.h>
#include <stdbool.h>

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
} list_s;

typedef list_s* list_t;

/* operations with memory */

void listRemove(list_t list);
list_t listInit(size_t lst_size);

void listInsertAtEnd(list_node_t node, list_t list);
void listInsertAtBegin(list_node_t node, list_t list);
void listInsert(size_t idx, list_node_t node, list_t list);

void listSort(list_t list);
void listErase(list_t list); 

/* algorithms for list */

void listPrint(list_t list);
void listReverseByPayloads(list_t list);
int listBsearch(list_t list, int number);

/* Macroses foreach */

#define FOREACH_NODE_FROM_END(i, list) \
  for (list_node_t node = list->last_node; \
       i < list->length; \
       i++, node = node->prev)

#define FOREACH_NODE_FROM_BEGIN(i, list) \
  for (list_node_t node = list->first_node; \
       i < list->length; \
       i++, node = node->next)

#endif // LIST_LIBRARY_H