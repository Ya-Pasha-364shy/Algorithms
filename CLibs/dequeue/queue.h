#ifndef DEQUEUE_LIBRARY_H
#define DEQUEUE_LIBRARY_H

#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <stdbool.h>

/** @brief
 * Очередь обладает быстрой вставкой
 * и быстрым удалением элементов
 * с начала и с конца - O(1). 
 * 
 * Чтение занимает время O(n),
 * где n - количество элементов очереди.
 * Количество итераций по списку = O(n). 
*/

struct dequeue;
struct dequeue_node;

typedef struct dequeue* dequeue_t;
typedef struct dequeue_node* dequeue_node_t;

/* operations with memory */

/**
 * @brief
 * Функция или метод, удаляющий очередь.
 * @param `dequeue` объект типа `dequeue_t`, если играет роль метода,
 * то должен быть таким же, что и вызывающий объект.
*/
void dequeueRemove(dequeue_t dequeue);

/**
 * @brief
 * Функция или метод,
 * удаляющая элемент с начала очереди, возвращает значение этого элемента
*/
int dequeuePop(dequeue_t dequeue);

/**
 * @brief
 * Функция или метод,
 * добавляющий элемент в конец очереди.
*/
void dequeuePush(dequeue_t dequeue, dequeue_node_t node);

/**
 * @brief
 * Функция или метод,
 * удаляющий элемент с конца и возвращающий значение этого элемента.
*/
int dequeuePopAtTheEnd(dequeue_t dequeue);

/**
 * @brief
 * Функция или метод,
 * добавляющая элемент в начало очереди
*/
void dequeuePushAtTheBegin(dequeue_t dequeue, dequeue_node_t node);

/**
 * @brief
 * Функция, инициализирующая новую очередь.
 * @param `nmemb` - количество элементов очереди.
 * @param `make_random_values` задаёт режим присвоения значений
 * объектам очереди. Если `false` - каждое значение иницилизируется нулём.
 * @return
 * Возвращает очередь объектов.
 * Гарантирует, что у каждого объекта имеется связность степени 1
*/
dequeue_t dequeueInit(size_t nmemb, bool make_random_values);

/**
 * @brief
 * Функция или метод, очищающая значения очереди, зануляя каждый элемент.
 * @param `dequeue` объект типа `dequeue_t`, если играет роль метода,
 * то должен быть таким же, что и вызывающий объект.
*/
void dequeueErase(dequeue_t dequeue); 

/**
 * @brief
 * Функция, удяляющая (высвобождающая память) элемент из очереди
 * по указанному индексу.
 * @param `dequeue` объект типа `dequeue_t`, если играет роль метода,
 * то должен быть таким же, что и вызывающий объект.
 * @param `index` индекс элемента очереди, что необходимо удалить
 * @result
 * Гарантирует, что связи между объектами, окружающими удалённый
 * элемент, будут переопределны должным образом.
*/
void dequeueRemoveNodeByIndex(dequeue_t dequeue, size_t index);

/* algorithms for dequeue */

/**
 * @brief
 * Функция, печатающая все элементы очереди
 * @param `name` имя очереди.
 * @param `dequeue` объект типа `dequeue_t`, если играет роль метода,
 * то должен быть таким же, что и вызывающий объект.
*/
void dequeuePrint(const char* name, dequeue_t dequeue);

/* Calls for initialize a two-way dequeue */

/**
 * @brief
 * Конструктор объектов типа dequeue_t. Выделяет динамическую
 * память в куче для создания объектов дву сторонней очереди.
 * @param `nmemb` число объектов очереди.
 * @param `make_random_values` задаёт режим присвоения значений
 * объектам очереди. Если `false` - каждое значение иницилизируется нулём.
 * @return
 * Возвращает созданную дву-сторонюю очередь с числом элементов `nmemb`.
*/
dequeue_t Dequeue(size_t nmemb, bool make_random_values);

/* some helpful methods */

/**
 * @brief
 * Инициализирует очередь теми значениями, количество
 * которых указано первым параметром, за ним идут сами значения.
 * @param nmemb количество значений, может быть = 0
 * @param __VA_ARGS__ значения
*/
dequeue_t init(int8_t nmemb, ...);

/**
 * @brief
 * Выполняет простой поиск в очереди до тех пор, пока не найдет такого элемента
 * в связном очереди.
 * Возвращает -1, если значение не найдено
 * @param dequeue двусвязный очередь типа `dequeue_t`
 * @param desired_node искомый узел типа `dequeue_node_t`
*/
int findIndexByElement(dequeue_t dequeue, dequeue_node_t desired_node);

/* defining of dequeue and dequeue_node by structs */

typedef struct dequeue_node {
  struct dequeue_node* prev;

  int payload;
} dequeue_node_s;

typedef dequeue_node_s* dequeue_node_t;

typedef struct dequeue {
  size_t length;

  dequeue_node_t last_node;
  dequeue_node_t first_node;

  void (*dequeueInsert)(struct dequeue* dequeue, dequeue_node_t node, size_t idx);

  int (*dequeuePop)(struct dequeue* dequeue);
  void (*dequeuePush)(struct dequeue* dequeue, dequeue_node_t node);

  int (*dequeuePopAtEnd)(struct dequeue* dequeue);
  void (*dequeuePushAtBegin)(struct dequeue* dequeue, dequeue_node_t node);

  void (*dequeueErase)(struct dequeue* dequeue);
  void (*dequeueRemove)(struct dequeue* dequeue);
} dequeue_s;

typedef dequeue_s* dequeue_t;

/* Macro foreach */

/**
 * @brief
 * Цикл foreach, начинающий обход очереди с начала
 * @param `i` счётчик, нужен для того, чтобы
 * остановиться на последнем элементе и случайно
 * не сделать полный цикл (начать итерироваться
 * с начала снова).
 * @param `dequeue` очередь элементов.
*/
#define FOREACH_NODE(i, dequeue) \
  i = 0; \
  for (dequeue_node_t node = dequeue->first_node; \
       i < dequeue->length; \
       ++i, node = node->prev)

/**
 * @brief
 * Цикл foreach, начинающий обход очереди с начала.
 * Его основная особенность в том, что здесь нет
 * перехода между элементами очереди. "Переход" ложится
 * на совесть программиста.
 * @param `i` счётчик цикла
 * @param `dequeue` очередь элементов
*/
#define FOREACH_NODE_FROM_BEGIN_WITHOUT_TRANSITION(i, dequeue) \
  i = dequeue->length; \
  for (dequeue_node_t node = dequeue->first_node; \
       i > 0; --i)

/* helpful macro */

#define LIKE(condition) __glibc_likely(condition)

#define UNLIKE(condition) __glibc_unlikely(condition)

#endif // DEQUEUE_LIBRARY_H