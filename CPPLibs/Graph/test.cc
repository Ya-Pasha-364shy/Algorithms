#include <cassert>
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
   * Отслеживаемый узел сейчас имеет метку = 3,
   * Конфигурация графа:
   * (1)---(0)---(2)
   *        \---(3)
  */
  my_graph.addNodeByKeyInEnd(4);
  /**
   * Отслеживаемый узел сейчас имеет метку = 4
   * Конфигурация графа:
   * (1)---(0)---(2)---(4)
   *        \----(3)
  */

  const Graph::GraphNode *current = my_graph.getTrackingNode();
  assert(current->getKey() == 4);
  assert(current->getParentNode()->getKey() == 2);
  assert(current->getParentNode()->getParentNode()->getKey() == 0);
  assert(current->getParentNode()->getParentNode()->getParentNode()->getKey() == 1);

  auto neighbours_of_parent_zero = current->getParentNode()->getParentNode()->getListEdges();
  for (auto it = neighbours_of_parent_zero.begin(); it != neighbours_of_parent_zero.end(); ++it) {
    std::cout << "Neighbour of zero: " << it->getRightNode()->getKey() << std::endl;
  }
  // *Output*
  // Neighbour of zero: 1
  // Neighbour of zero: 2
  // Neighbour of zero: 3

  // ищем путь до последнего элемента графа (4)
  if (my_graph.BreadthFirstSearch(my_graph.getTrackingNode()) == true) {
    std::cout << "Path is finded !" << std::endl;
  }

  std::cout << "Testing of Dijkstra's algorithm" << std::endl;

  Graph test_dijkstra;
  test_dijkstra.addNodeByKeyInBegin(0, 0);
  test_dijkstra.addNodeByKeyInEnd(2, 2);
  test_dijkstra.addNodeByKeyToParentOfTracking(1, 6);
  test_dijkstra.addNodeByKeyInEnd(3, 4);
  test_dijkstra.addNodeByKeyInEnd(4, 1);

  test_dijkstra.addBidirectionalLinkBetweenTwoNodes(1, 2, 1);
  test_dijkstra.addBidirectionalLinkBetweenTwoNodes(1, 3, 4);
  
  /**
   * (0)<---6--->(1)<---4---->
   *  \           \           \
   *   2          1            4      
   *    \          \            \
   *     \<---2--->(2)<---4--->(3)<---1--->(4)
  */

  uint64_t cost_path_to_end = test_dijkstra.leastWeightPathSearch();
  assert(cost_path_to_end == 7);
  std::cout << "[1] result cost = " << cost_path_to_end << std::endl;
  
  test_dijkstra.addBidirectionalLinkBetweenTwoNodes(1, 4, 1);
  cost_path_to_end = test_dijkstra.leastWeightPathSearch();
  assert(cost_path_to_end == 4);
  std::cout << "[2] result cost = " << cost_path_to_end << std::endl;
  

  return EXIT_SUCCESS;
}