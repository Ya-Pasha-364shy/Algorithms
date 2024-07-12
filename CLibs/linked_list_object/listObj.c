#include "listObj.h"

void listObjInit(list_obj_t *list) {
  list->prev = list;
  list->next = list;
}

static inline void __listObjAdd(list_obj_t *needle_node, list_obj_t *prev, list_obj_t *next) {
  assert(next->prev == prev  || prev->next == next ||
          needle_node != prev || needle_node != next);

  next->prev        = needle_node;
  needle_node->next = next;
  needle_node->prev = prev;
  prev->next        = needle_node;
}

void listObjAdd(list_obj_t *node, list_obj_t *head) {
  __listObjAdd(node, head, head->next);
}

void listObjAddTail(list_obj_t *node, list_obj_t *head) {
  __listObjAdd(node, head->prev, head);
}

static inline void __listObjDel(list_obj_t *prev, list_obj_t *next) {
  next->prev = prev;
  prev->next = next;
}

static inline void __listObjDelEntry(list_obj_t *entry) {
  list_obj_t *prev, *next;

  prev = entry->prev;
  next = entry->next;

  assert(prev != NULL && next != NULL);

  __listObjDel(entry->prev, entry->next);
}

void listObjDel(list_obj_t *entry) {
  __listObjDelEntry(entry);
}

void listObjDelInit(list_obj_t *entry) {
  __listObjDelEntry(entry);
  listObjInit(entry);
}

void listObjReplace(list_obj_t *old, list_obj_t *node) {
  node->next = old->next;
  node->next->prev = node;
  node->prev = old->prev;
  node->prev->next = node;
}

bool listObjEmpty(const list_obj_t *head) {
  return head->next == head;
}

bool listObjIsInited(const list_obj_t *head) {
  return head->next != NULL;
}

static inline void __listObjSplice(const list_obj_t *list,
                                   list_obj_t *prev, list_obj_t *next)
{
  list_obj_t *first = list->next;
  list_obj_t *last = list->prev;

  first->prev = prev;
  prev->next = first;

  last->next = next;
  next->prev = last;
}

void listObjSplice(const list_obj_t *list, list_obj_t *head) {
  if (!listObjEmpty(list)) {
      __listObjSplice(list, head, head->next);
  }
}

void listObjSpliceTail(list_obj_t *list, list_obj_t *head) {
  if (!listObjEmpty(list)) {
      __listObjSplice(list, head->prev, head);
  }
}

void listObjSpliceInit(list_obj_t *list, list_obj_t *head) {
  if (!listObjEmpty(list)) {
      __listObjSplice(list, head, head->next);
      listObjInit(list);
  }
}

void listObjSpliceTailInit(list_obj_t *list, list_obj_t *head) {
  if (!listObjEmpty(list)) {
      __listObjSplice(list, head->prev, head);
      listObjInit(list);
  }
}

static inline void __listObjDelItem(list_obj_t *ditem,
                                    list_obj_t *dnext,
                                    list_obj_t *dprev)
{
  dnext->prev = dprev;
  dprev->next = dnext;
}

void listObjDelItem(list_obj_t *delete_item, list_obj_t *list) {
  if (!listObjEmpty(list) && delete_item) {
      __listObjDelItem(delete_item, delete_item->next, delete_item->prev);
  }
}