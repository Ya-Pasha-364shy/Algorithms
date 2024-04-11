#include <iostream>
#include "BTS.hpp"

namespace BinaryTreeSearch {

BTS::BTS() {
  root_node = NULL;
}

const BTSNode* BTS::getNode() {
	return root_node;
}

void BTS::printTree(const BTSNode *node, int level)
{
	if (node) {
	  printTree(node->left, level + 1);

		for (int i = 0; i < level; ++i) {
			std::cout << "   ";
    }

		std::cout << node->key << std::endl;
		printTree(node->right, level + 1);
	}
}

int BTS::searchKeyInTreeRecursive(int key, const BTSNode* node)
{
  if (node == NULL) {
    node = getNode();
  }

	if (key == node->key) {
		return key;
  } else if (key < node->key) {
		std::cout << node->key << " ";
		return searchKeyInTreeRecursive(key, node->left);
	} else {
		std::cout << node->key << " ";
		return searchKeyInTreeRecursive(key, node->right);
	}
}

int BTS::searchByKey(int key)
{
	const BTSNode *current_node = getNode();
	while (current_node != NULL and
         key != current_node->key)
  {
		if (key < current_node->key) {
			current_node = current_node->left;
    } else {
			current_node = current_node->right;
    }
	}
	return key;
}

void BTS::insertNodeByKey(int key)
{
	if ((key > 0) and root_node != NULL) {
		insertNodeInTreeByKey(key, root_node);
	} else {
		root_node = new BTSNode;
		root_node->key = key;
		root_node->left = NULL;
		root_node->right = NULL;
	}
}

void BTS::insertNodeInTreeByKey(int key, BTSNode* node)
{
	if (key < node->key) {
		if (node->left != NULL) {
			insertNodeInTreeByKey(key, node->left);
		} else {
			node->left = new BTSNode;
			node->left->key = key;
			node->left->left = NULL;
			node->left->right = NULL;
		}
	}
	else if (key >= node->key) {
		if (node->right != NULL) {
			insertNodeInTreeByKey(key, node->right);
    } else {
			node->right = new BTSNode;
			node->right->key = key;
			node->right->left = NULL;
			node->right->right = NULL;
		}
	}
}

void BTS::deleteTree(BTSNode *root_node) {
	if (root_node != NULL) {
		deleteTree(root_node->left);
		deleteTree(root_node->right);
	}
	delete root_node;
}

BTS::~BTS() {
	deleteTree(root_node);
}

}; // namespace BinaryTreeSearch