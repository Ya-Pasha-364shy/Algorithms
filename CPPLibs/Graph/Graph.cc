#include <queue>
#include <cassert>
#include <iostream>

#include "Graph.hpp"

namespace graph {

void Graph::addNodeByKeyInEnd(uint64_t key) {
  GraphNode *new_node = new GraphNode(key); 

  if (not start_node_exists()) {
    /* в графе ещё нет узлов, создаём начальный */
    start_node = new_node;
    current_node = start_node;
    // finish_node === NULL
  } else if (finish_node_exists()) {
    new_node->setParentNode(finish_node);
    /* создаём ребро между узлами нулевого веса */
    GraphEdge edge(finish_node, new_node,
                   GRAPH_EDGE_BIDIRECTIONAL);
    finish_node->addEdgeToList(edge);
    new_node->addEdgeToListReverse(edge);

    finish_node = new_node;
    current_node = finish_node;
  } else { // finish_node == NULL
    new_node->setParentNode(current_node);
    finish_node = new_node;
    /* создаём ребро между узлами нулевого веса */
    GraphEdge edge(current_node, finish_node,
                    GRAPH_EDGE_BIDIRECTIONAL);
    current_node->addEdgeToList(edge);
    finish_node->addEdgeToListReverse(edge);

    current_node = finish_node;
  }
  ++counter_of_nodes;
}

void Graph::addNodeByKeyInBegin(uint64_t key) {
  GraphNode *new_node = new GraphNode(key);

  if (not start_node_exists()) {
    start_node = new_node;
    current_node = start_node;
  } else {
    /* определяем новый корень */
    // new_node->parent === NULL;
    start_node->setParentNode(new_node);
    if (not finish_node_exists()) {
      /* в случае, когда в графе существует только один узел */
      finish_node = start_node;
    }
    current_node = new_node;

    /* создаём ребро между узлами нулевого веса */
    GraphEdge edge(current_node, start_node,
                   GRAPH_EDGE_BIDIRECTIONAL);
    current_node->addEdgeToList(edge);
    start_node->addEdgeToListReverse(edge);

    start_node = new_node;
  }
  ++counter_of_nodes;
}

void Graph::addNodeByKeyToParentOfTracking(uint64_t key) {
  GraphNode *new_node = new GraphNode(key);

  if (not start_node_exists()) {
    // граф пуст, добавляем первую вершину
    start_node = new_node;
    current_node = start_node;
  } else if (current_node != NULL) {
    GraphNode *parent_node_of_current = getParentNode();
    new_node->setParentNode(parent_node_of_current);
    current_node = new_node;

    GraphEdge edge(parent_node_of_current, current_node,
                   GRAPH_EDGE_BIDIRECTIONAL);
    parent_node_of_current->addEdgeToList(edge);
    current_node->addEdgeToListReverse(edge);

    if (not finish_node_exists()) {
      finish_node = new_node;
    }
  }
  ++counter_of_nodes;
}

void Graph::removeNodeByKey(uint64_t key) {
  // pass
}


bool Graph::BreadthFirstSearch(const GraphNode *searched_node,
                               const GraphNode *start_node) {
  if (searched_node == NULL and finish_node_exists()) {
    searched_node = finish_node;
  }
  if (start_node == NULL and start_node_exists()) {
    start_node = this->start_node;
  }
  if (not searched_node or not start_node) {
    return false;
  }
  hash_visited_node.erase(hash_visited_node.begin(), hash_visited_node.end());

  bool is_running = true;
  uint64_t neighbour_key = 0, searched_key = searched_node->getKey();
  GraphNode *current_neighbour = NULL;
  std::queue<const GraphNode *> queue_of_neighbours;
  // std::list<GraphNode *> shortest_way_to_searched;

  queue_of_neighbours.push(start_node);
  hash_visited_node[start_node->getKey()] = true;

  while (not queue_of_neighbours.empty() and is_running) {
    const GraphNode *tracking_node = queue_of_neighbours.front();
    queue_of_neighbours.pop();

    std::list<GraphEdge> edges_to_neighbours = tracking_node->getListEdges();
    for (auto iterator = edges_to_neighbours.begin(); iterator != edges_to_neighbours.end();
         ++iterator)
    {
      current_neighbour = iterator->getRightNode();
      if (current_neighbour == NULL) {
        assert(true == false);
      }
      neighbour_key = current_neighbour->getKey();

      if (neighbour_key == searched_key) {
        is_running = false;
        break;
      }

      if (not hash_visited_node[neighbour_key]) {
        hash_visited_node.at(neighbour_key) = true;
        queue_of_neighbours.push(current_neighbour);
      }
    }
  }

  // TODO(K1rch):
  // нужно построить дерево поиска (не бинарное), которое бы возвращало наикратчайший путь до точки
  // assert(not shortest_way_to_searched.empty());
  hash_visited_node.erase(hash_visited_node.begin(), hash_visited_node.end());
  return (not is_running) ? true : false; 
}

void Graph::DijkstraPathSearch(GraphNode *searched_node,
                               GraphNode *start_node) {
  // pass
}

void Graph::getAllNodes(std::deque<const GraphNode *>& accumulator,
                        GraphNode *tracking_node) {
  if (tracking_node == NULL) {
    if (start_node == NULL and finish_node == NULL) {
      return;
    }
    tracking_node = start_node;
  }
  uint64_t link_key = 0, this_key = tracking_node->getKey();
  // list of edges can't be empty if graph is linked
  // TODO(K1rch): support empty case after supporting not linked graph
  std::list<GraphEdge> edges = tracking_node->getListEdges();

  if (hash_visited_node[this_key] == false) {
    accumulator.push_front(tracking_node);
    hash_visited_node.at(this_key) = true;
  }

  auto it = edges.begin();
  for (; it != edges.end(); ++it) {
    link_key = it->getRightNode()->getKey();
    if (hash_visited_node[link_key] == false) {
      break;
    }
  }
  if (it == edges.end()) {
    // все соседи уже были обойдены - отслеживаемая вершина крайняя
    return;
  }

  GraphNode *link_node = NULL;
  for (it = edges.begin(); it != edges.end(); ++it) {
    link_node = it->getRightNode();
    link_key = link_node->getKey();

    if (hash_visited_node[link_key] == false) {
      hash_visited_node.at(link_key) = true;
      accumulator.push_front(link_node);
      getAllNodes(accumulator, link_node);
    }
  }

}

void Graph::removeGraph() {
  std::deque<const GraphNode *> all_nodes;
  getAllNodes(all_nodes);

  std::cout << "counter_of_nodes = " << counter_of_nodes << std::endl;
  std::cout << "all_nodes.size()" << all_nodes.size() << std::endl;

  assert(counter_of_nodes == all_nodes.size());

  size_t all_nodes_count = all_nodes.size();
  for (auto i = all_nodes_count; i != 0; --i) {
    const GraphNode* node = *all_nodes.begin();
    all_nodes.pop_front();
    delete node;
  }
  counter_of_nodes = 0;

}

Graph::~Graph() {
  removeGraph();
}

}; // namespace graph