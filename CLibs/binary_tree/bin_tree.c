#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <time.h>

#include "bin_tree.h"

static void rng_init() {
    static bool rng_inited = false;
    if (!rng_inited) {
        srand(time(NULL));
        rng_inited = true;
    }
}

bin_tree_t *bin_tree_init() {
    bin_tree_t *tree = calloc(1, sizeof(bin_tree_t));
    if (!tree) {
        perror("bin_tree_init failed: ");
        return NULL;
    }
    rng_init();
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

void _bin_tree_print(bin_tree_t **tree_wrap) {
    if (!tree_wrap) {
        fprintf(stderr, "<%s>: invalid wrapper\n", __func__);
        return;
    }
    bin_tree_print(*tree_wrap);
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

static bool greater_comparator(const int a, const int b) {
    return a > b;
}

static bool less_eq_comparator(const int a, const int b) {
    return a <= b;
}

static void split_rec(bin_tree_node_t *_subtree, bin_tree_t *tree, const int split_val, int *cnt, bool (*comp)(const int,  const int)) {
    if (!_subtree) {
        return;
    }
    if (!cnt) {
        fprintf(stderr, "<%s>: Invalid cnt\n", __func__);
        return;
    }

    int test_key = _subtree->key;
    if (comp(test_key, split_val)) {
        if (!bin_tree_insert(tree, test_key)) {
            fprintf(stderr, "<%s>: Failed to insert in tmp tree\n", __func__);
            return;
        }
        (*cnt)++;
    }

    split_rec(_subtree->left, tree, split_val, cnt, comp);
    split_rec(_subtree->right, tree, split_val, cnt, comp);

    return;
}

static bin_tree_t *merge_trees(bin_tree_t *left, bin_tree_t *right, bool choice) {
    if (!left || !right) {
        return NULL;
    }
    bin_tree_node_t *tmp = NULL;
    bin_tree_t *res = left;

    if (choice) {
        tmp = left->root;
        if (!tmp) {
            return right;
        }

        while (tmp->right) {
            tmp = tmp->right;
        }
        tmp->right = right->root;
    } else {
        tmp = right->root;
        if (!tmp) {
            return left;
        }

        while (tmp->left) {
            tmp = tmp->left;
        }
        tmp->left = left->root;
        res = right;
    }
    return res;
}

static bool split_and_merge_by_x(bin_tree_t **tree, const int x) {
    if (!tree || !*tree) {
        fprintf(stderr, "<%s>: tree is NULL\n", __func__);
        return false;
    }

    bin_tree_t *src = *tree, *lbt = NULL, *rbt = NULL, *mid = NULL,
               *tmp = NULL, *res = NULL;

    int lcnt = 0;
    int rcnt = 0;

    /* allocate helper trees */
    if (!(lbt = bin_tree_init())) goto fail;
    if (!(rbt = bin_tree_init())) goto fail;
    if (!(mid = bin_tree_init())) goto fail;

    if (!bin_tree_insert(mid, x)) goto fail;

    /* split */
    split_rec(src->root, lbt, x, &lcnt, less_eq_comparator);
    split_rec(src->root, rbt, x, &rcnt, greater_comparator);

    /* merge left + mid */
    bool use_left = (lcnt > 1);

    tmp = merge_trees(lbt, mid, use_left);
    if (!tmp) goto fail;

    if (use_left) {
        if (lbt->root) {
            free(mid);
            mid = NULL;
        } else {
            free(lbt);
            lbt = NULL;
        }
    } else {
        if (mid->root) {
            free(lbt);
            lbt = NULL;
        } else {
            free(mid);
            mid = NULL;
        }
    }

    /* random choice for final merge */
    int n = lcnt + rcnt + 1;
    int m = rand() % n;
    bool attach_left = (m < lcnt);

    res = merge_trees(tmp, rbt, attach_left);
    if (!res) goto fail;

    if (attach_left) {
        if (tmp->root) {
            free(rbt);
            rbt = NULL;
        } else {
            free(tmp);
            tmp = NULL;
        }
    } else {
        if (rbt->root) {
            free(tmp);
            tmp = NULL;
        } else {
            free(rbt);
            rbt = NULL;
        }
    }

    /* destroy old source tree */
    bin_tree_destroy(tree);
    *tree = res;
    return true;

 fail:
    if (lbt) bin_tree_destroy(&lbt);
    if (rbt) bin_tree_destroy(&rbt);
    if (mid) bin_tree_destroy(&mid);
    if (tmp) bin_tree_destroy(&tmp);
    return false;
}

bool bin_tree_balanced_insert(bin_tree_t **tree, int new_node_value) {
    bool res = split_and_merge_by_x(tree, new_node_value);
    if (!res) {
        fprintf(stderr, "<%s>: split_and_merge_by_x failed\n", __func__);
    }
    return res;
}