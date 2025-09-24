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

    if (bin_tree_insert(test_tree, 10)) {
        printf("10 added !\n");
    } else {
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

    if (bin_tree_insert(test_tree, 5)) {
        printf("5 added !\n");
    } else {
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

    if (bin_tree_insert(test_tree, 15)) {
        printf("15 added !\n");
    } else {
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

    if (bin_tree_insert(test_tree, 25)) {
        printf("25 added !\n");
    } else {
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

    if (bin_tree_insert(test_tree, 3)) {
        printf("3 added !\n");
    } else {
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

    if (bin_tree_insert(test_tree, 2)) {
        printf("2 added !\n");
    } else {
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

    if (bin_tree_insert(test_tree, 7)) {
        printf("7 added !\n");
    } else {
        rc = EXIT_FAILURE;
        goto destroy_and_exit;

    }

    if (bin_tree_insert(test_tree, 99)) {
        printf("99 added !\n");
    } else {
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

    bin_tree_print(test_tree);

    if (bin_tree_search(test_tree, 15)) {
        printf("\"15\" finded successfully !\n");
    } else {
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

    if (!bin_tree_search(test_tree, 100)) {
        printf("\"100\" cannot be find, success !\n");
    } else {
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

    if (bin_tree_search(test_tree, 3)) {
        printf("\"3\" finded successfully !\n");
    } else {
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

    if (!bin_tree_search(test_tree, 0)) {
        printf("\"0\" cannot be find, success !\n");
    } else {
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

    if (bin_tree_erase(test_tree, 3)) {
        printf("3 erased !\n");
    } else {
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

    if (bin_tree_erase(test_tree, 25)) {
        printf("25 erased !\n");
    } else {
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

    if (!bin_tree_search(test_tree, 3)) {
        printf("\"3\" cannot be find, success !\n");
    } else {
        rc = EXIT_FAILURE;
        goto destroy_and_exit;
    }

destroy_and_exit:
    bin_tree_destroy(&test_tree);
    bin_tree_print(test_tree);
    return rc;
}