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
}

void Graph::addNodeByKeyToParentOfTracking(uint64_t key) {
  GraphNode *new_node = new GraphNode(key);

  if (not start_node_exists()) {
    // граф пуст, добавляем первую вершину
    start_node = new_node;
    current_node = start_node;
  } else if (current_node != NULL) {
    GraphNode *parent_node_of_current = getParentNode();
    if (parent_node_of_current != NULL) {
      return;
    }
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
}

void Graph::removeNodeByKey(uint64_t key) {
  // pass
}

void Graph::BreadthFirstSearch(GraphNode *searched_node,
                               GraphNode *start_node) {
  // pass
}

void Graph::DijkstraPathSearch(GraphNode *searched_node,
                               GraphNode *start_node) {
  // pass
}

void Graph::getAllNodes(std::deque<const GraphNode *>& accumulator,
                        GraphNode *tracking_node) {
  if (tracking_node == NULL) {
    tracking_node = start_node;
  }
  uint64_t link_key = 0, this_key = tracking_node->getKey();
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
    // все соседи уже были обойдены - отслеживаемый узел крайний.
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

  size_t all_nodes_count = all_nodes.size();
  for (auto i = all_nodes_count; i != 0; --i) {
    const GraphNode* node = *all_nodes.begin();
    all_nodes.pop_front();
    delete node;
  }
}

Graph::~Graph() {
  removeGraph();
}

}; // namespace graph