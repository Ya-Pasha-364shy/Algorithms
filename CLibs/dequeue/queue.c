#include "queue.h"
#include <limits.h>

static inline void setToDefaultsNode(dequeue_node_t node) {
  node->prev = NULL;
  node->payload = 0;
}

void dequeueRemove(dequeue_t dequeue) {
  if (LIKE(dequeue == NULL)) {
    return;
  }
  size_t iterator;
  dequeue_node_t tmp_cursor;
  FOREACH_NODE_FROM_BEGIN_WITHOUT_TRANSITION(iterator, dequeue) {
    tmp_cursor = node->prev;
    free(node);
    // manual transition
    node = tmp_cursor;
    dequeue->length--;
  }
  free(dequeue);
}

int dequeuePop(dequeue_t dequeue) {
  if (dequeue == NULL) {
    return INT_MIN;
  }
  dequeue_node_t node_to_rm = dequeue->first_node;
  dequeue->first_node = dequeue->first_node->prev;
  int returned_payload = node_to_rm->payload;
  free(node_to_rm);
  dequeue->length--;

  return returned_payload;
}

void dequeuePush(dequeue_t dequeue, dequeue_node_t node) {
  if (dequeue == NULL || node == NULL) {
    return;
  }
  node->prev = NULL;
  dequeue->last_node->prev = node;
  dequeue->last_node = node;
  dequeue->length++;
}

int dequeuePopAtTheEnd(dequeue_t dequeue) {
  int returned_payload;
  if (dequeue == NULL) {
    return INT_MIN;
  } else if (dequeue->length == 1) {
    returned_payload = dequeue->last_node->payload;
    dequeueRemove(dequeue);
    return dequeue->last_node->payload;
  }

  size_t iterator;
  dequeue_node_t node_to_rm = dequeue->last_node;
  returned_payload = node_to_rm->payload;
  dequeue_node_t prev_node_of_removed_node = NULL;
  FOREACH_NODE(iterator, dequeue) {
    if (node == node_to_rm) {
      break;
    }
    prev_node_of_removed_node = node;
  }
  dequeue->length--;
  free(node_to_rm);

  prev_node_of_removed_node->prev = NULL;
  dequeue->last_node = prev_node_of_removed_node;

  return returned_payload;
}

void dequeuePushAtTheBegin(dequeue_t dequeue, dequeue_node_t node) {
  if (dequeue == NULL || node == NULL) {
    return;
  }
  node->prev = dequeue->first_node;
  dequeue->first_node = node;
}


dequeue_t dequeueInit(size_t size, bool make_random_values) {
  dequeue_t dequeue = calloc(1, sizeof(dequeue_s));
  if (dequeue == NULL) {
    return NULL;
  }
  dequeue->length = size;
  if (LIKE(size == 0)) {
    return dequeue;
  }
  dequeue->first_node = malloc(sizeof(dequeue_node_s));
  if (dequeue->first_node == NULL) {
    return NULL;
  }
  setToDefaultsNode(dequeue->first_node);  
  srand(time(NULL));
  if (make_random_values) {
    dequeue->first_node->payload = rand() % 100;
  } else {
    dequeue->first_node->payload = 0;
  }
  dequeue_node_t cursor_on_previous = dequeue->first_node;

  for (size_t i = 1; i < size; ++i) {
    dequeue_node_t tmp = malloc(sizeof(dequeue_node_s));
    setToDefaultsNode(tmp);

    if (make_random_values) {
      tmp->payload = rand() % 100;
    } else {
      tmp->payload = 0;
    }
    cursor_on_previous->prev = tmp;
    cursor_on_previous = tmp;
  }
  dequeue->last_node = cursor_on_previous;
  return dequeue;
}

void dequeueErase(dequeue_t dequeue) {
  size_t iterator;
  FOREACH_NODE_FROM_BEGIN_WITHOUT_TRANSITION(iterator, dequeue) {
    node->payload = 0;
    node = node->prev;
  }
}

void dequeueRemoveNodeByIndex(dequeue_t dequeue, size_t index) {
  if (index >= dequeue->length) {
    return;
  } else if (dequeue->length == 1) {
    return (void)dequeuePop(dequeue);
  }

  size_t iterator;
  dequeue_node_t prev_node = NULL;
  FOREACH_NODE(iterator, dequeue) {
    if (index == iterator) {
      prev_node->prev = node->prev;
      free(node);      
      break;
    }
    prev_node = node;
  }
}

void dequeuePrint(const char* name, dequeue_t dequeue) {
  if (name == NULL || dequeue == NULL) {
    return;
  }
  printf("%s = [ ", name);
  dequeue_node_t iterator = dequeue->first_node;
  for (size_t i = 0; i < dequeue->length; i++) {
    printf(" %d ", iterator->payload);
    iterator = iterator->prev;
  }
  printf(" ]\n");
}


dequeue_t Dequeue(size_t nmemb, bool make_random_values) {
  dequeue_t this = dequeueInit(nmemb, make_random_values);

  this->dequeuePop = &dequeuePop;
  this->dequeuePush = &dequeuePush;
  this->dequeuePopAtEnd = &dequeuePopAtTheEnd;
  this->dequeuePushAtBegin = &dequeuePushAtTheBegin;

  this->dequeueErase = &dequeueErase;
  this->dequeueRemove = &dequeueRemove;

  return this;
}

dequeue_t init(int8_t nmemb, ...) {
  dequeue_t dequeue = Dequeue(0, false);
  va_list args;
  va_start(args, nmemb);
  for (unsigned i = 0; i < nmemb; i++) {
    dequeue_node_t node = calloc(1, sizeof(dequeue_node_s));
    node->payload = va_arg(args, unsigned int);
    dequeuePush(dequeue, node);
  }
  va_end(args);

  return dequeue;
}

int findIndexByElement(dequeue_t dequeue, dequeue_node_t desired_node) {
  if (dequeue == NULL || desired_node == NULL) {
    return INT_MIN;
  }
  
  size_t iterator;
  FOREACH_NODE(iterator, dequeue) {
    if (node == desired_node) {
      return iterator;
    }
  }
}