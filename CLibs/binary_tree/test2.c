
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "bin_tree.h"

int main(void) {
    int rc = EXIT_SUCCESS;
    bin_tree_t *test_tree = bin_tree_init();
    if (!test_tree) {
        return EXIT_FAILURE;
    }

    srand((unsigned)time(NULL));

    // Вставляем 1000 случайных значений
    for (int i = 0; i < 1000; i++) {
        int val = rand() % 10000;
        if (!bin_tree_insert(test_tree, val)) {
            fprintf(stderr, "insert %d failed\n", val);
            rc = EXIT_FAILURE;
            goto destroy_and_exit;
        }
    }

    // Удаляем 500 случайных значений
    for (int i = 0; i < 500; i++) {
        int val = rand() % 10000;
        bin_tree_erase(test_tree, val);
    }

    // Добавляем ещё 500 значений
    for (int i = 0; i < 500; i++) {
        int val = rand() % 10000;
        bin_tree_insert(test_tree, val);
    }

    // Удаляем ВСЕ значения от 0 до 9999 (гарантированно должны очистить дерево)
    for (int val = 0; val < 10000; val++) {
        bin_tree_erase(test_tree, val);
    }

destroy_and_exit:
    bin_tree_destroy(&test_tree);
    return rc;
}
