#ifndef THE_GRAPH_HPP
#define THE_GRAPH_HPP

#include <map>
#include <list>
#include <deque>
#include <stdint.h>

namespace graph {
  
class Graph {
  /**
   * @brief
   * значение бесконечного веса используется для
   * поиска накратчайшего пути от одной вершины до 
   * другой.
  */
  static const uint32_t infinity_weight = UINT32_MAX;

 public:
  struct GraphEdge;

  enum GraphEdgeType : uint8_t {
    /* задаёт несвязный граф */
    GRAPH_EDGE_INVALID = 0x00,
    /* задаёт неориентированный связный граф */
    GRAPH_EDGE_BIDIRECTIONAL = 0x01,
    /** 
     * задаёт ориентированный связный граф,
     * однако возможна комбинация с типом BIDERECTIONAL.
    */
    GRAPH_EDGE_UNIDIRECTIONAL_LEFT = 0x02,
    GRAPH_EDGE_UNIDIRECTIONAL_RIGHT = 0xFD,
  };

  struct GraphNode {
    GraphNode(uint64_t _key, GraphNode *_parent_node=NULL) {
      key = _key;
      parent_node = _parent_node;
    }

    void addEdgeToList(GraphEdge& _edge) {
      list_edges.emplace_back(_edge);
    }

    void addEdgeToListReverse(GraphEdge& _edge_to_reverse) {
      _edge_to_reverse.swapLeftAndRightNodesIfNeeded();
      list_edges.emplace_back(_edge_to_reverse);
    }

    void setParentNode(GraphNode *_parent_node) {
      parent_node = _parent_node;
    }

    GraphNode *getParentNode() const {
      return parent_node;
    }

    inline std::list<GraphEdge> getListEdges() const {
      return list_edges;
    }

    inline std::list<GraphEdge>& getListEdges() {
      return list_edges;
    }

    inline uint64_t getKey() const {
      return key;
    }

   private:
    uint64_t key;
    GraphNode *parent_node = NULL;
    /**
     * @details
     * был выбран список, так как он
     * позволяет делать динамическую
     * вставку (удаление) в начало и в конец за O(1),
     * без растрат на время расширения capacity, с переводом
     * всех элементов на новые адреса в памяти.
     * TODO: заменить на свой linked_list.
    */
    std::list<GraphEdge> list_edges;
  };

  struct GraphEdge {

    GraphEdge(GraphNode *_left_node, GraphNode *_right_node,
              GraphEdgeType _type, uint32_t _weight=0)
    {
      type = _type;
      weight = _weight;
      left_node = _left_node;
      right_node = _right_node;
    }

    void swapLeftAndRightNodesIfNeeded() {
      if (type >= GRAPH_EDGE_BIDIRECTIONAL) {
        GraphNode *tmp = left_node;
        left_node = right_node;
        right_node = tmp;
        // TODO: зачем ? 
        if (type != GRAPH_EDGE_BIDIRECTIONAL) {
          type = static_cast<GraphEdgeType>(~type);
        }
      }
    }

    inline GraphNode *getLeftNode() const {
      return left_node;
    }

    inline GraphNode *getRightNode() const {
      return right_node;
    }

    inline uint32_t getWeight() const {
      return weight;
    }

   private:
    GraphEdgeType type = GRAPH_EDGE_INVALID;
    /**
     * Если граф не взвешанный, то вес
     * имеет значение 0 - по-умолчанию.
    */
    uint32_t weight = 0;
    /**
     * каждое ребро графа
     * должно связывать только
     * две вершины между собой.
     */
    GraphNode *left_node = NULL;
    GraphNode *right_node = NULL;
  };

  Graph() = default;

  /**
   * @brief
   * Создаёт узел, добавляя в граф и 
   * помечая его как конечный. Если
   * узлов в графе нет, то помечает его как начальный.
   * Иначе добавляет его, делая родителем отслеживаемый (current).
   * @param key метка нового узла
   * @param weight вес ребра, соедниняющего прошлый конечный узел и
   * текущий конечный
  */
  void addNodeByKeyInEnd(uint64_t key, uint32_t weight=0);

  /**
   * @brief
   * Создаёт узел, добавляя в граф и
   * помечая его как стартовый.
   * Если граф не пуст, то сдвигает текущий
   * стартовый узел таким образом, чтобы он оказался
   * дочерним для нового созданного. Если пуст - добавляет новый элемент.
   * @param key метка нового узла
   * @param weight вес ребра соеднияющего прошлый стартовый узел
   * и текущий начальный
  */
  void addNodeByKeyInBegin(uint64_t key, uint32_t weight=0);

  /**
   * @brief
   * Создаёт узел, который входит во множество узлов
   * родительского узла относительно отслеживаемого (current).
   * В результате меняет значение последнего отслеживаемого
   * @param key метка нового узла
   * @param weight вес ребра, соединяющего присоеднияющего узла к
   * его родителю.
  */
  void addNodeByKeyToParentOfTracking(uint64_t key, uint32_t weight=0);

  /**
   * @brief
   * Создаёт двусторонее соеднинение между двумя узлами
   * @param lkey метка первого узла
   * @param rkey метка второго узла
   * @param weight вес соединения между узлами
  */
  void addBidirectionalLinkBetweenTwoNodes(uint64_t lkey, uint64_t rkey, uint32_t weight);

  /**
   * @brief
   * Находит узел, который отображает значение `key`.
   * @param key метка узла для удаления.
  */
  void removeNodeByKey(uint64_t key);

  /**
   * @brief
   * Осуществляет поиск кратчайшего пути
   * между двумя вершинами невзвешанного связанного графа.
   * Сложность алгоритма поиска в ширину = O(V+E).
   * 
   * @param searched_node точка до которой искать путь.
   * Если принимает значение NULL, то интерпретируется
   * как самая последняя вершина графа.
   * @param start_node точка от которой искать путь.
   * Если принимает значение NULL, то интерпретируется
   * как самая первая вершина графа. NULL по-умолчанию.
   * @return true, если вершина найдена, иначе false
   * TODO: возвращать кратчайший путь от start_node до searched_node
  */
  bool BreadthFirstSearch(const GraphNode *searched_node=NULL,
                          const GraphNode *start_node=NULL);

  /**
   * @brief
   * Осуществляет поиск кратчайшего пути между двумя
   * вершинами взвешанного связанного графа, используя
   * алгоритм Дейкстры.
   * @param searched_node точка до которой искать путь.
   * Если принимает значение NULL, то интерпретируется
   * как самая последняя вершина графа.
   * @param start_node точка от которой искать путь.
   * Если принимает значение NULL, то интерпретируется
   * как самая первая вершина графа. NULL по-умолчанию.
   * @return возвращает стоимость пути до searched_node.
  */
  uint64_t leastWeightPathSearch(const GraphNode *searched_node=NULL,
                                 const GraphNode *start_node=NULL);

  /**
   * @brief
   * Удаляет граф, высвобождая память из кучи,
   * выделенную под узлы.
  */
  void removeGraph();

  inline bool start_node_exists() const {
    return start_node != NULL ? true : false;
  }

  inline bool finish_node_exists() const {
    return finish_node != NULL ? true : false;
  }

  GraphNode *getParentNode() const {
    return current_node != NULL ?
             current_node->getParentNode() : NULL;
  }

  const GraphNode *getTrackingNode() const {
    return current_node;
  }

  ~Graph();

 private:
  /**
   * @brief
   * приватный метод, осуществляющий поиск всех вершин графа в глубину,
   * посредством хвостовой рекурсии, алгоритм DFS.
   * @param accumulator двусторонняя очередь, в которой лежат указатели на все
   * области памяти, которые интерпретируются как узлы графа.
   * @param tracking_node узел, соседи которого рассматрвиаются в данный момент
  */
  void getAllNodes(std::deque<GraphNode *>& accumulator,
                   GraphNode *tracking_node=NULL);


  void initHashOfCostsNodes();

  std::pair<const GraphEdge *, bool>
  findLowestCostEdge(const GraphNode *tracking_node);

  bool need_to_collect = false;

  uint32_t counter_of_nodes = 0;
  /* "точка старта" */
  GraphNode *start_node = NULL;
  /* "точка выхода" */
  GraphNode *finish_node = NULL;
  /* указывает на последний рассматриваемый узел */
  GraphNode *current_node = NULL;

  /**
   * хэш-таблица соотвествий номера узла и
   * метки о том, был ли этот узел уже посещён.
  */
  std::map<uint64_t, bool> hash_visited_node;
  /**
   * Хэш-таблица соотвествий номера узла
   * и стоимости пути до этого узла
  */
  std::map<uint64_t, uint64_t> hash_node_weight;
};

};
#endif // THE_GRAPH_HPP