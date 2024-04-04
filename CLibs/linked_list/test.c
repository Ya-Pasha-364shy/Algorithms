#include <stdio.h>

#include "list.h"

static list_node_t TEST_FUNCTION createRandomNode() {
  list_node_t node = calloc(1, sizeof(list_node_s));
  if (!node) {
    return NULL;
  }
  node->payload = rand() % 100;
  return node;
}

int main(void) {
  // size_t nmemb;
  // printf("Get lenght of list: "); scanf("%ld", &nmemb);

  list_t lst = init(3, 1, 2, 3);

  if (lst == NULL)
    return EXIT_FAILURE;

  list_node_t node1 = createRandomNode();
  list_node_t node2 = createRandomNode();
  list_node_t node3 = createRandomNode();

  lst->listInsertAtBegin(lst, node1);
  lst->listInsertAtBegin(lst, node2);
  lst->listInsertAtBegin(lst, node3);

  printf("[before] node1 index = %d; node value = %d\n", findIndexByElement(lst, node1), node1->payload);
  printf("[before *by idx*] node1 index = 0; node value = %d\n", findElementByIndex(lst, 0)->payload);
  
  lst = listSort(lst);
  printf("[after]  node1 index = 0; node value = %d\n", findElementByIndex(lst, 0)->payload);

  printf("====\n");
  size_t iterator;
  FOREACH_NODE_FROM_BEGIN(iterator, lst) {
    printf("payload = %d\n", node->payload);
  }
  printf("====\n");
  FOREACH_NODE_FROM_END(iterator, lst) {
    printf("payload = %d\n", node->payload);
  }
  printf("====\n");


  lst->listRemove(lst);

  return EXIT_SUCCESS;  
}