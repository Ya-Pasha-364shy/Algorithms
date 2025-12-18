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
    bin_tree_t **tree_wrap = &test_tree;

    // Вставляем возрастающую последовательность
    // НЕ используйте bin_tree_balanced_insert для слишком больших циклов
    // (см. test3.c)
    for (int i = 1; i <= 1000; i++) {
        if (!bin_tree_balanced_insert(tree_wrap, i)) {
            fprintf(stderr, "insert %d failed\n", i);
            rc = EXIT_FAILURE;
            goto destroy_and_exit;
        }
    }

    printf("Inserted 1'000 elements in ascending order\n");
    test_tree = *tree_wrap;

    // Проверяем несколько выборочных значений
    if (!bin_tree_search(test_tree, 1)) {
        fprintf(stderr, "Search for 1 failed\n");
        rc = EXIT_FAILURE;
    }
    if (!bin_tree_search(test_tree, 50)) {
        fprintf(stderr, "Search for 50 failed\n");
        rc = EXIT_FAILURE;
    }
    if (!bin_tree_search(test_tree, 100)) {
        fprintf(stderr, "Search for 100 failed\n");
        rc = EXIT_FAILURE;
    }
    if (!bin_tree_search(test_tree, 500)) {
        fprintf(stderr, "Search for 500 failed\n");
        rc = EXIT_FAILURE;
    }
    if (!bin_tree_search(test_tree, 1000)) {
        fprintf(stderr, "Search for 1000 failed\n");
        rc = EXIT_FAILURE;
    }

    // Удалим середину и край
    bin_tree_erase(test_tree, 1);
    bin_tree_erase(test_tree, 50);
    bin_tree_erase(test_tree, 1000);

    // Проверим, что удалённые действительно не находятся
    if (bin_tree_search(test_tree, 1)  ||
        bin_tree_search(test_tree, 50) ||
        bin_tree_search(test_tree, 1000))
    {
        fprintf(stderr, "Erase check failed\n");
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

destroy_and_exit:
    bin_tree_destroy(tree_wrap);
    return rc;
}
