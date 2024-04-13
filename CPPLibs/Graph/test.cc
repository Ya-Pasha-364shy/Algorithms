#include <iostream>
#include "Graph.hpp"

using namespace graph;

int main() {
  Graph my_graph;

  my_graph.addNodeByKeyInBegin(0);
  /**
   * Отслеживаемый узел сейчас имеет метку = 0.
   * Конфигурация графа:
   * (0)
  */
  my_graph.addNodeByKeyInBegin(1);
  /**
   * Отслеживаемый узел сейчас имеет метку = 1.
   * Конфигурация графа:
   * (1)---(0)
  */
  my_graph.addNodeByKeyInEnd(2);
  /**
   * Отслеживаемый узел сейчас имеет метку = 2,
   * Конфигурация графа:
   * (1)---(0)---(2)
  */
  my_graph.addNodeByKeyToParentOfTracking(3);
  /**
   * Отслеживаемый узел сейчас имеетм метку = 3,
   * Конфигурация графа
   * (1)---(0)---(2)
   *        \---(3)
  */

  return EXIT_SUCCESS;
}