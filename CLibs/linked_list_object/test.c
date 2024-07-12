#include <stdio.h>
#include <assert.h>

#include <listObj.h>

typedef struct A {
  int a;
  int b;

  list_obj_t list_entry;
} A;

typedef struct B {
  int c;
  int d;

  list_obj_t list_entry;
} B;

int main(int argc, char *argv[]) {

  A base   = { .a = 0, .b = 0 };
  A first  = { .a = 1, .b = 1 };
  A second = { .a = 2, .b = 2 };

  B third  = { .c = 3, .d = 3 };

  listObjInit(&base.list_entry);
  listObjAddTail(&second.list_entry, &base.list_entry);
  listObjAdd(&first.list_entry, &base.list_entry);

  list_obj_t *pos, *next = { NULL };
  A *iterator = NULL;

  FOREACH_NODE(pos, &base.list_entry) {
    iterator = list_obj_entry(pos, A, list_entry);
    printf(".a = %d\n", iterator->a);
  }
  printf("\n");

  void *another_iterator = NULL;

  /* пусть B наследуется от A */
  listObjAddTail(&third.list_entry, &base.list_entry);

  /* тогда мы можем достучаться до него как к структуре "типа A" */
  FOREACH_NODE(pos, &base.list_entry) {
    another_iterator = (void *)list_obj_entry(pos, A, list_entry);
    printf(".a = %d\n", ((struct A *)another_iterator)->a);
  }

  return 0;
}