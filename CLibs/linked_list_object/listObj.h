#ifndef LIST_OBJECT_LIBRARY_H
#define LIST_OBJECT_LIBRARY_H

#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <stdbool.h>
#include <assert.h>

/** @brief
 * Здесь представлены объявления методов и элементов,
 * используемых в списке объектов.
 * 
 * Список обладает быстрой вставкой
 * и быстрым удалением элементов
 * с начала и с конца - O(1). 
 * 
 * Чтение занимает время O(n),
 * где n - количество элементов списка.
 * Количество итераций по списку = O(n). 
*/

struct list_obj_node_s;

/* operations with memory */

typedef struct list_obj_node_s {
  struct list_obj_node_s *next;
  struct list_obj_node_s *prev;
} list_obj_t;

#define container_of(ptr, type, member) (type *)((uint8_t *)ptr - offsetof(type, member))

/**
 * @brief
 * Макрос, возвращающий указатель сам объект.
 * @param ptr итератор списка объектов
 * @param type тип который итератор хранит в себе
 * @param member имя элемента типа list_node_t
 * 
 */
#define list_obj_entry(ptr, type, member) container_of(ptr, type, member)

/**
 * @brief
 * Функция инициализирующая связный список объектов.
 * После выполнения этой фукции, связный список будет состоять всего из одного
 * элемента и будет в состоянии закольцованности
 */
void listObjInit(list_obj_t *list);

/**
 * @brief
 * Функция, добавляющая элемент node сразу после head
 */
void listObjAdd(list_obj_t *node, list_obj_t *head);

/**
 * @brief
 * Функция, добавляющая элемент node в конец
 */
void listObjAddTail(list_obj_t *node, list_obj_t *head);

/**
 * @brief
 * Функция, удаляющая элемент entry из связности
 * prev - entry - next
 * В итоге звено entry выходит из этой цепочки
 */
void listObjDel(list_obj_t *entry);

/**
 * @brief
 * Функция, выполняющая тоже самое, что и предыдущая за исключением того, что
 * она также выполняет линковку элемента самого на себя - более безопасно
 */
void listObjDelInit(list_obj_t *entry);

void listObjReplace(list_obj_t *old, list_obj_t *node);

bool listObjEmpty(const list_obj_t *head);

bool listObjIsInited(const list_obj_t *head);

void listObjSplice(const list_obj_t *list, list_obj_t *head);

void listObjSpliceTail(list_obj_t *list, list_obj_t *head);

void listObjSpliceInit(list_obj_t *list, list_obj_t *head);

void listObjSpliceTailInit(list_obj_t *list, list_obj_t *head);

void listObjDelItem(list_obj_t *delete_item, list_obj_t *list);

/* Macro foreach */

#define FOREACH_NODE(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#define FOREACH_NODE_FROM_POS(pos, head) \
    for (; pos != (head); pos = pos->next)

#define FOREACH_NODE_REVERSE(pos, head) \
    for (pos = (head)->prev; pos != (head); pos = pos->prev)

#define FOREACH_NODE_SAFE(pos, n, head) \
    for (pos = (head)->next, n = pos->next; \
        pos != (head); \
        pos = n, n = pos->next)

#define FOREACH_NODE_REVERSE_SAFE(pos, n, head) \
    for (pos = (head)->prev, n = pos->prev; \
        pos != (head); \
        pos = n, n = pos->prev)

#define FOREACH_NODE_SAFE_BY_ITERATOR(pos, head, i, length) \
    for (pos = (head)->next; \
         i < length; \
         ++i, pos = pos->next)


/* helpful macro */

#define LIKE(condition) __glibc_likely(condition)

#define UNLIKE(condition) __glibc_unlikely(condition)

#endif // LIST_OBJECT_LIBRARY_H