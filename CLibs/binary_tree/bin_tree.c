#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#include "bin_tree.h"

bin_tree_t *bin_tree_init() {
    bin_tree_t *tree = calloc(1, sizeof(bin_tree_t));
    if (!tree) {
        perror("bin_tree_init failed: ");
        return NULL;
    }
    return tree;
}

static bin_tree_node_t *bin_tree_node_init(int value) {
    bin_tree_node_t *node = calloc(1, sizeof(bin_tree_node_t));
    if (!node) {
        perror("bin_tree_node_init failed: ");
        return NULL;
    }
    node->key = value;
    return node;
}

static void bin_tree_destroy_rec(bin_tree_node_t *subtree) {
    if (subtree == NULL) {
        return;
    }
    bin_tree_destroy_rec(subtree->left);
    bin_tree_destroy_rec(subtree->right);

    free(subtree);
    subtree = NULL;
}

void bin_tree_destroy(bin_tree_t **tree) {
    if (!tree || !*tree) {
        fprintf(stderr, "<%s>: tree is NULL already\n", __func__);
        return;
    }
    bin_tree_t *target_tree = *tree;
    bin_tree_destroy_rec(target_tree->root);
    free(target_tree);
    target_tree = NULL;
    *tree = target_tree;
}

bool bin_tree_insert(bin_tree_t *tree, int new_node_value) {
    if (!tree) {
        fprintf(stderr, "<%s>: tree is NULL\n", __func__);
        return false;
    }
    bin_tree_node_t *tmp = NULL, **saved_transit = NULL;

    if (!tree->root) {
        tmp = bin_tree_node_init(new_node_value);
        if (!tmp) {
            fprintf(stderr, "<%s>: failed to create node for inserting\n", __func__);
            return false;
        }
        tree->root = tmp;
        return true;
    }
    tmp = tree->root;

    do {
        if (tmp->key > new_node_value) {
            saved_transit = &tmp->left;
            tmp = tmp->left;
        } else {
            saved_transit = &tmp->right;
            tmp = tmp->right;
        }
    } while (tmp);

    tmp = bin_tree_node_init(new_node_value);
    if (!tmp) {
        fprintf(stderr, "<%s>: failed to insert value after find corresponding place\n", __func__);
        return false;
    }
    *saved_transit = tmp;

    return true;
}

bool bin_tree_erase(bin_tree_t *tree, int erase_node_value) {
    if (!tree) {
        fprintf(stderr, "<%s>: tree is NULL\n", __func__);
        return false;
    }
    if (!tree->root) {
        fprintf(stderr, "<%s>: root is NULL\n", __func__);
        return false;
    }
    bin_tree_node_t *tmp = tree->root, **saved_transit = NULL;

    do {
        if (tmp->key > erase_node_value) {
            saved_transit = &tmp->left;
            tmp = tmp->left;
        } else if (tmp->key < erase_node_value) {
            saved_transit = &tmp->right;
            tmp = tmp->right;
        } else {
            break;
        }
    } while (tmp);

    if (tmp) {
        if (saved_transit) {
            bin_tree_destroy_rec(*saved_transit);
            *saved_transit = NULL;
        } else {
            bin_tree_destroy_rec(tree->root);
            tree->root = NULL;
        }
    } else {
        return false;
    }
    return true;
}


static void bin_tree_print_rec(bin_tree_node_t *node, int level) {
    if (node == NULL) {
        return;
    }
    bin_tree_print_rec(node->left, level+1);
    bin_tree_print_rec(node->right, level+1);

    printf("lvl:%d: %d\n", level, node->key);
}

void bin_tree_print(bin_tree_t *tree) {
    if (!tree) {
        fprintf(stderr, "<%s>: tree is NULL\n", __func__);
        return;
    }
    if (!tree->root) {
        fprintf(stderr, "<%s>: root is NULL\n", __func__);
        return;
    }

    printf("===\n");
    bin_tree_print_rec(tree->root->left, 1);
    printf("r = %d\n", tree->root->key);
    bin_tree_print_rec(tree->root->right, 1);
    printf("===\n");
}

bool bin_tree_search(bin_tree_t *tree, int search_value) {
    if (!tree) {
        fprintf(stderr, "<%s>: tree is NULL\n", __func__);
        return false;
    }
    if (!tree->root) {
        fprintf(stderr, "<%s>: root is NULL\n", __func__);
        return false;
    }

    bin_tree_node_t *tmp = tree->root;
    while (tmp) {
        int key_to_check = tmp->key;
        if (key_to_check > search_value) {
            tmp = tmp->left;
        } else if (key_to_check < search_value) {
            tmp = tmp->right;
        } else {
            return true;
        }
    }
    return false;
}
