#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bin_tree.h"

int main(void) {
    int rc = EXIT_SUCCESS;
    bin_tree_t *test_tree = bin_tree_init();
    if (!test_tree) {
        return EXIT_FAILURE;
    }

    // Вставляем возрастающую последовательность
    for (int i = 1; i <= 10000; i++) {
        if (!bin_tree_insert(test_tree, i)) {
            fprintf(stderr, "insert %d failed\n", i);
            rc = EXIT_FAILURE;
            goto destroy_and_exit;
        }
    }

    printf("Inserted 10,000 elements in ascending order\n");

    // Проверяем несколько выборочных значений
    if (!bin_tree_search(test_tree, 5000)) {
        fprintf(stderr, "Search for 5000 failed\n");
        rc = EXIT_FAILURE;
    }
    if (!bin_tree_search(test_tree, 9999)) {
        fprintf(stderr, "Search for 9999 failed\n");
        rc = EXIT_FAILURE;
    }

    // Удалим середину и край
    bin_tree_erase(test_tree, 1);
    bin_tree_erase(test_tree, 5000);
    bin_tree_erase(test_tree, 10000);

    // Проверим, что удалённые действительно не находятся
    if (bin_tree_search(test_tree, 1) ||
        bin_tree_search(test_tree, 5000) ||
        bin_tree_search(test_tree, 10000)) {
        fprintf(stderr, "Erase check failed\n");
        rc = EXIT_FAILURE;
    }

destroy_and_exit:
    bin_tree_destroy(&test_tree);
    return rc;
}
