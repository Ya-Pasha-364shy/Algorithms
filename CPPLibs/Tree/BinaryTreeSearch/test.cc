#include <iostream>

#include "BTS.hpp"

using namespace BinaryTreeSearch;

int main() {

  BTS my_binary_search_tree;
  my_binary_search_tree.insertNodeByKey(20);
  my_binary_search_tree.insertNodeByKey(10);
  my_binary_search_tree.insertNodeByKey(30);

  my_binary_search_tree.printTree(my_binary_search_tree.getNode(), 0);

  return EXIT_SUCCESS;
}