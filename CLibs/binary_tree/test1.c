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

    // вставляем
    int values_to_insert[] = {10, 5, 15, 25, 3, 2, 7, 99};
    for (size_t i = 0; i < sizeof(values_to_insert)/sizeof(values_to_insert[0]); i++) {
        if (!bin_tree_insert(test_tree, values_to_insert[i])) {
            fprintf(stderr, "insert %d failed\n", values_to_insert[i]);
            rc = EXIT_FAILURE;
            goto destroy_and_exit;
        }
    }

    bin_tree_print(test_tree);

    // поиск
    if (!bin_tree_search(test_tree, 99)) {
        fprintf(stderr, "99 not found!\n");
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

    // удаляем несколько
    int values_to_erase[] = {3, 25, 10};
    for (size_t i = 0; i < sizeof(values_to_erase)/sizeof(values_to_erase[0]); i++) {
        if (!bin_tree_erase(test_tree, values_to_erase[i])) {
            fprintf(stderr, "erase %d failed\n", values_to_erase[i]);
            rc = EXIT_FAILURE;
            goto destroy_and_exit;
        }
    }

destroy_and_exit:
    bin_tree_destroy(&test_tree);
    return rc;
}