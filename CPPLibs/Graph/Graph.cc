#include <queue>
#include <cassert>
#include <iostream>

#include "Graph.hpp"

namespace graph {

void Graph::addNodeByKeyInEnd(uint64_t key, uint32_t weight) {
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
                   GRAPH_EDGE_BIDIRECTIONAL, weight);
    finish_node->addEdgeToList(edge);
    new_node->addEdgeToListReverse(edge);

    finish_node = new_node;
    current_node = finish_node;
  } else { // finish_node == NULL
    new_node->setParentNode(current_node);
    finish_node = new_node;
    /* создаём ребро между узлами нулевого веса */
    GraphEdge edge(current_node, finish_node,
                   GRAPH_EDGE_BIDIRECTIONAL, weight);
    current_node->addEdgeToList(edge);
    finish_node->addEdgeToListReverse(edge);

    current_node = finish_node;
  }
  ++counter_of_nodes;
  need_to_collect = true;
}

void Graph::addNodeByKeyInBegin(uint64_t key, uint32_t weight) {
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

    /* создаём ребро между узлами */
    GraphEdge edge(current_node, start_node,
                   GRAPH_EDGE_BIDIRECTIONAL, weight);
    current_node->addEdgeToList(edge);
    start_node->addEdgeToListReverse(edge);

    start_node = new_node;
  }
  ++counter_of_nodes;
  need_to_collect = true;
}

void Graph::addNodeByKeyToParentOfTracking(uint64_t key, uint32_t weight) {
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
                   GRAPH_EDGE_BIDIRECTIONAL, weight);
    parent_node_of_current->addEdgeToList(edge);
    current_node->addEdgeToListReverse(edge);

    if (not finish_node_exists()) {
      finish_node = new_node;
    }
  }
  ++counter_of_nodes;
  need_to_collect = true;
}

void Graph::addBidirectionalLinkBetweenTwoNodes(uint64_t lkey,
                                                uint64_t rkey,
                                                uint32_t weight)
{
  static std::deque<GraphNode *> all_nodes;
  if (need_to_collect) {
    if (not all_nodes.empty()) {
      all_nodes.clear();
    }
    hash_visited_node.erase(hash_visited_node.begin(),
                            hash_visited_node.end());
    getAllNodes(all_nodes);
    need_to_collect = false;
  }
  assert(all_nodes.size() == counter_of_nodes);

  GraphNode *lkey_node = NULL, *rkey_node = NULL;
  for (auto node: all_nodes) {
    if (node->getKey() == lkey) {
      lkey_node = node;
    } else if (node->getKey() == rkey) {
      rkey_node = node;
    }
  }
  if (not lkey_node or not rkey_node) {
    return;
  }

  GraphEdge edge(lkey_node, rkey_node,
                 GRAPH_EDGE_BIDIRECTIONAL, weight);
  lkey_node->addEdgeToList(edge);
  rkey_node->addEdgeToListReverse(edge);
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

    const std::list<GraphEdge> edges_to_neighbours = tracking_node->getListEdges();
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

  return (not is_running) ? true : false; 
}

uint64_t Graph::leastWeightPathSearch(const GraphNode *searched_node,
                                      const GraphNode *start_node) {
  if (searched_node == NULL) {
    searched_node = finish_node;
  }
  if (start_node == NULL) {
    start_node = this->start_node;
  }
  if (not start_node or not searched_node) {
    return 0;
  }
  /**
   * обнуляем хэш посещённых вершин 
  */
  hash_visited_node.erase(hash_visited_node.begin(),
                          hash_visited_node.end());
  /**
   * обнуляем хэш стоимостей до узлов
  */
  initHashOfCostsNodes();
  hash_node_weight[start_node->getKey()] = 0;

  const auto edges_to_neighbours = start_node->getListEdges();
  for (auto iterator = edges_to_neighbours.begin();
       iterator != edges_to_neighbours.end(); ++iterator) {
    /**
     * безусловно меняем значения цен для соседей стартовой вершины
    */
    hash_node_weight[iterator->getRightNode()->getKey()] =
      iterator->getWeight();
  }
  hash_visited_node[start_node->getKey()] = true;

  uint64_t select_node_cost = 0;
  uint64_t lowest_cost_node_key = 0;
  const GraphNode *tracking_node = start_node;
  /**
   * 1) получаем ребро до соседа с минимальной стоимостью
  */
  auto lowest_cost_pair = findLowestCostEdge(tracking_node);
  const GraphEdge *lowest_cost_edge = NULL;
  if (lowest_cost_pair.second != false) {
    lowest_cost_edge = lowest_cost_pair.first;
  }

  while (true) {
    GraphNode *lowest_cost_node = lowest_cost_edge->getRightNode();
    lowest_cost_node_key = lowest_cost_node->getKey();
    select_node_cost = hash_node_weight[lowest_cost_node_key];

    uint64_t new_cost_from_selected = 0;
    /**
     * 2) получаем соседей узла относительно tracking_node
    */
    const std::list<GraphEdge> neighbours_of_selected =
      lowest_cost_edge->getRightNode()->getListEdges();

    for (auto edge: neighbours_of_selected) {
      new_cost_from_selected = edge.getWeight() + select_node_cost;
      /* обновляем веса соседей, если к соседу можно добраться быстрее через выбранный узел */
      if (new_cost_from_selected < hash_node_weight[edge.getRightNode()->getKey()]) {
        hash_node_weight[edge.getRightNode()->getKey()] = new_cost_from_selected;
      }
    }
    // помечаем данный узел как обойденный, так как по всем его рёбрам мы прошли.
    hash_visited_node[lowest_cost_node_key] = true;

    /**
     * 3) повторяем до тех пор, пока не будет выполнено для всех узлов графа
    */
    tracking_node = lowest_cost_node;
    if (tracking_node->getKey() == searched_node->getKey()) {
      break;
    }
    lowest_cost_pair = findLowestCostEdge(tracking_node);
    if (lowest_cost_pair.second != false) {
      lowest_cost_edge = lowest_cost_pair.first;
    } else {
      break;
    }
  }

  return hash_node_weight[searched_node->getKey()];
}

void Graph::getAllNodes(std::deque<GraphNode *>& accumulator,
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

void Graph::initHashOfCostsNodes() {
  std::deque<GraphNode *> all_nodes;
  hash_visited_node.erase(hash_visited_node.begin(),
                          hash_visited_node.end());

  getAllNodes(all_nodes);
  const GraphNode *node = NULL;
  uint64_t key = 0;
  assert(counter_of_nodes == all_nodes.size());

  for (uint32_t i = 0; i < counter_of_nodes; ++i) {
    node = all_nodes.front();
    key = node->getKey();
    hash_node_weight[key] = infinity_weight;
    hash_visited_node[key] = false;
    all_nodes.pop_front();
  }
  assert(hash_visited_node[key] == false);
}

std::pair<const Graph::GraphEdge *, bool>
Graph::findLowestCostEdge(const GraphNode *tracking_node)
{
  const std::list<GraphEdge> edges_to_neighbours = tracking_node->getListEdges();

  auto iterator = edges_to_neighbours.begin();
  auto selected_path = edges_to_neighbours.begin();

  uint64_t accumulator_tmp = 0;
  uint64_t tracking_node_cost = hash_node_weight[tracking_node->getKey()];
  assert(tracking_node_cost != infinity_weight);
  GraphNode *next_node = NULL;

  for (; iterator != edges_to_neighbours.end(); ++iterator) {
    if (hash_visited_node[iterator->getRightNode()->getKey()] == true) {
      continue;
    }

    accumulator_tmp = tracking_node_cost + iterator->getWeight();
    if (not next_node or
        accumulator_tmp < (tracking_node_cost + selected_path->getWeight()))
    {
      next_node = iterator->getRightNode();
      selected_path = iterator;
      continue;
    }
  }
  return {&*selected_path, next_node != NULL};
}

void Graph::removeGraph() {
  std::deque<GraphNode *> all_nodes;
  hash_visited_node.erase(hash_visited_node.begin(), hash_visited_node.end());
  getAllNodes(all_nodes);

  assert(counter_of_nodes == all_nodes.size());

  size_t all_nodes_count = all_nodes.size();
  for (auto i = all_nodes_count; i != 0; --i) {
    const GraphNode* node = *all_nodes.begin();
    all_nodes.pop_front();
    delete node;
  }
  counter_of_nodes = 0;
  hash_visited_node.erase(hash_visited_node.begin(), hash_visited_node.end());
}

Graph::~Graph() {
  removeGraph();
}

}; // namespace graph