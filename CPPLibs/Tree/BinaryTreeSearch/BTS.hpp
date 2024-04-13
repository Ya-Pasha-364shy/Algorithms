#ifndef BINARY_TREE_SEARCH_HPP
#define BINARY_TREE_SEARCH_HPP

#include <iostream>
#include <fstream>

namespace BinaryTreeSearch {

struct BTSNode {
	int key;
	BTSNode* left;
	BTSNode* right;
};

class BTS {
 public:
	BTS();

	const BTSNode *getNode();

	void printTree(const BTSNode *node, int level);

	void deleteTree(BTSNode *root_node);

	void insertNodeByKey(int key);

	int searchKeyInTreeRecursive(int key, const BTSNode *node);

	int searchByKey(int key);

	~BTS();

 private:
	BTSNode *root_node = NULL;

	void insertNodeInTreeByKey(int key, BTSNode* node);
};

}; // namespace BinaryTreeSearch

#endif // BINARY_TREE_SEARCH_HPP