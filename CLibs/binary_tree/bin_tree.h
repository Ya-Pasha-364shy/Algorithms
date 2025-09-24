#ifndef BINARY_TREE_SEARCH_H
#define BINARY_TREE_SEARCH_H

typedef struct bin_tree_node_s {
    int key;
    struct bin_tree_node_s *left;
    struct bin_tree_node_s *right;
} bin_tree_node_t;

typedef struct bin_tree_s {
    bin_tree_node_t *root;
} bin_tree_t;

bin_tree_t *bin_tree_init();

void bin_tree_destroy(bin_tree_t **tree);

bool bin_tree_insert(bin_tree_t *tree, int new_node_value);

bool bin_tree_erase(bin_tree_t *tree, int erase_node_value);

void bin_tree_print(bin_tree_t *tree);

bool bin_tree_search(bin_tree_t *tree, int search_value);

#endif // BINARY_TREE_SEARCH_H