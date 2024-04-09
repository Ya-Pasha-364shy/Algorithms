#ifndef LIST_LIBRARY_H
#define LIST_LIBRARY_H

#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <stdbool.h>

/**
 * @brief
 * директива для пометок функций
 * для теста.
*/
#define TEST_FUNCTION

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

/**
 * @brief
 * Функция или метод, удаляющий список.
 * @param `list` объект типа `list_t`, если играет роль метода,
 * то должен быть таким же, что и вызывающий объект.
*/
void listRemove(list_t list);

/**
 * @brief
 * Функция, инициализирующая новый список.
 * @param `nmemb` - количество элементов списка.
 * @param `make_random_values` задаёт режим присвоения значений
 * объектам списка. Если `false` - каждое значение иницилизируется нулём.
 * @return
 * Возвращает список объектов.
 * Гарантирует, что у каждого объекта имеется связность степени 2
*/
list_t listInit(size_t nmemb, bool make_random_values);

/**
 * @brief
 * Функция или метод, вставляющий указанный элемент в конец списка.
 * @param `list` объект типа `list_t`, если играет роль метода,
 * то должен быть таким же, что и вызывающий объект.
 * @param `node` объект, который необходимо вставить в конец
 * дву-связного списка.
*/
void listInsertAtEnd(list_t list, list_node_t node);

/**
 * @brief
 * Функция или метод, вставляющий указанный элемент в начало списка.
 * @param `list` объект типа `list_t`, если играет роль метода,
 * то должен быть таким же, что и вызывающий объект.
 * @param `node` объект, который необходимо вставить в начало
 * дву-связного списка.
*/
void listInsertAtBegin(list_t list, list_node_t node);

/**
 * @brief
 * Функция, вставляющая указанный элемент по указанному индексу в список.
 * @param `list` объект типа `list_t`, если играет роль метода,
 * то должен быть таким же, что и вызывающий объект.
 * @param `node` объект, который необходимо вставить в список.
 * @param `idx` индекс, по которому будет произведена вставка `node`.
*/
void listInsert(list_t list, list_node_t node, size_t idx);

/**
 * @brief
 * Функция или метод, очищающая значения списка, зануляя каждый элемент.
 * @param `list` объект типа `list_t`, если играет роль метода,
 * то должен быть таким же, что и вызывающий объект.
*/
void listErase(list_t list); 

/**
 * @brief
 * Функция, удяляющая (высвобождающая память) элементы из списка.
 * @param `list` объект типа `list_t`, если играет роль метода,
 * то должен быть таким же, что и вызывающий объект.
*/
void listRemoveAllNodes(list_t list);

/**
 * @brief
 * Функция, удяляющая (высвобождающая память) элемент из списка
 * по указанному индексу.
 * @param `list` объект типа `list_t`, если играет роль метода,
 * то должен быть таким же, что и вызывающий объект.
 * @param `index` индекс элемента списка, что необходимо удалить
 * @result
 * Гарантирует, что связи между объектами, окружающими удалённый
 * элемент, будут переопределны должным образом.
*/
void listRemoveNodeByIndex(list_t list, size_t index);

/**
 * @brief
 * Функция, удаляющая элемент с конца списка
*/
void listRemoveNodeFromEnd(list_t list);

/**
 * @brief
 * Функция, удаляющая элемент с начала
*/
void listRemoveNodeFromBegin(list_t list);

/* algorithms for linked list */

/**
 * @brief
 * Функция, печатающая все элементы списка
 * @param `name` имя списка.
 * @param `list` объект типа `list_t`, если играет роль метода,
 * то должен быть таким же, что и вызывающий объект.
*/
void listPrint(const char* name, list_t list);

/**
 * @brief
 * Функция, производящая быструю сортировку 
 * в среднем случае за O(n*log(n)) (худший O(n^2)),
 * посредством рекурсии.
 * @param `list` объект типа `list_t`, если играет роль метода,
 * то должен быть таким же, что и вызывающий объект.
 * @return
 * Возвращает указатель на отсортированный список.
 * Гарантирует, что исходный список будет удалён (его память высвобождена).
*/
list_t listSort(list_t list);

/**
 * @brief
 * Функция, разворачивающая список по значениям
 * (без перемещения сегментов памяти !)
 * @param `list` объект типа `list_t`, если играет роль метода,
 * то должен быть таким же, что и вызывающий объект.
*/
void listReverseByPayloads(list_t list);

// TODO(K1rch): реализовать
// int listBsearch(list_t list, int number);

/* Calls for initialize a two-way list */

/**
 * @brief
 * Конструктор объектов типа list_t. Выделяет динамическую
 * память в куче для создания объектов списка.
 * @param `nmemb` число объектов списка.
 * @param `make_random_values` задаёт режим присвоения значений
 * объектам списка. Если `false` - каждое значение иницилизируется нулём.
 * @return
 * Возвращает созданный список с числом элементов `nmemb`.
 * Гарантирует, что каждый объект этого списка имеет
 * двух-сторонюю связность.
*/
list_t List(size_t nmemb, bool make_random_values);

/* some helpful methods */

/**
 * @brief
 * Инициализирует спискок теми значениями, количество
 * которых указано первым параметром, за ним идут сами значения.
 * @param nmemb количество значений, может быть = 0
 * @param __VA_ARGS__ значения
*/
list_t init(int8_t nmemb, ...);


/**
 * @brief
 * Выполняет простой поиск в списке до тех пор, пока не найдет такого элемента
 * в связном списке.
 * Возвращает -1, если значение не найдено
 * @param list двусвязный список типа `list_t`
 * @param desired_node искомый узел типа `list_node_t`
*/
int findIndexByElement(list_t list, list_node_t desired_node);

/**
 * @brief
 * Выполняет простой поиск в списке до тех пор, пока не найдет элемента,
 * индекс которого соотвествует переданному. Возвращает NULL, если такой элемент
 * не найден.
 * @param list двусвязный список типа `list_t`
 * @param desired_node_index индекс искомого узла
*/
list_node_t findElementByIndex(list_t list, size_t desired_node_index);

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
  void (*listRemoveNodeFromEnd)(struct list* list);
  void (*listRemoveNodeFromBegin)(struct list* list);

  void (*listInsertAtEnd)(struct list* list, list_node_t node);
  void (*listInsertAtBegin)(struct list* list, list_node_t node);
  void (*listInsert)(struct list* list, list_node_t node, size_t idx);

  // struct list* (*listSort)(struct list* list);
  void (*listErase)(struct list* list);
} list_s;

typedef list_s* list_t;

/* Macro foreach */

/**
 * @brief
 * Цикл foreach, начинающий обход списка с конца
 * @param `i` счётчик, нужен для того, чтобы
 * остановиться на первом элементе и случайно
 * не сделать полный цикл (начать итерироваться
 * с конца снова).
 * @param `list` список элементов.
*/
#define FOREACH_NODE_FROM_END(i, list) \
  i = 0; \
  for (list_node_t node = list->last_node; \
       i < list->length; \
       ++i, node = node->prev)

/**
 * @brief
 * Цикл foreach, начинающий обход списка с начала
 * @param `i` счётчик, нужен для того, чтобы
 * остановиться на последнем элементе и случайно
 * не сделать полный цикл (начать итерироваться
 * с начала снова).
 * @param `list` список элементов.
*/
#define FOREACH_NODE_FROM_BEGIN(i, list) \
  i = 0; \
  for (list_node_t node = list->first_node; \
       i < list->length; \
       ++i, node = node->next)

/**
 * @brief
 * Цикл foreach, начинающий обход списка с конца.
 * Его основная особенность в том, что здесь нет
 * перехода между элементами списка. "Переход" ложится
 * на совесть программиста.
 * @param `i` счётчик цикла
 * @param `list` список элементов
*/
#define FOREACH_NODE_FROM_END_WITHOUT_TRANSITION(i, list) \
  i = list->length; \
  for (list_node_t node = list->last_node; \
       i > 0; --i)

/* helpful macro */

#define LIKE(condition) __glibc_likely(condition)

#define UNLIKE(condition) __glibc_unlikely(condition)

#endif // LIST_LIBRARY_H