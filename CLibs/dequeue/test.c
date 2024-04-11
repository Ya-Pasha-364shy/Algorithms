#include <stdlib.h>
#include <assert.h>

#include "queue.h"

static dequeue_node_t createRandomNode() {
  dequeue_node_t node = calloc(1, sizeof(dequeue_node_s));
  if (!node) {
    return NULL;
  }
  node->payload = rand() % 100;
  return node;
}


int main(void) {
  // dequeue_t dequeue = init(3, 1, 2, 3);
  dequeue_t dequeue = init(0);
  if (dequeue == NULL)
    return EXIT_FAILURE;

  dequeue_node_t node1 = createRandomNode();
  dequeue_node_t node2 = createRandomNode();
  dequeue_node_t node3 = createRandomNode();

  dequeue->dequeuePush(dequeue, node1);
  dequeue->dequeuePush(dequeue, node2);
  dequeue->dequeuePushAtBegin(dequeue, node3);

  printf("[before] node1 index = %d; node value = %d\n", findIndexByElement(dequeue, node1), node1->payload);
  dequeuePrint("my_dequeue", dequeue);

  assert(dequeue->length == 3);

  dequeuePop(dequeue);
  dequeuePop(dequeue);
  dequeuePopAtTheEnd(dequeue);

  assert(dequeue->length == 0);

  dequeueRemove(dequeue);

  return EXIT_SUCCESS;
}