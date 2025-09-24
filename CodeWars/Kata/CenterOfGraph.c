#include <stdio.h>
#include <stddef.h>

/**
 * Description:
 * find center of the star graph
 */

typedef struct Graph_Edge_Pair {
    unsigned a;
    unsigned b;
} edge;

unsigned center(size_t length, edge graph_edges[length]) {
    unsigned answer = 0;
    unsigned max_pow = 0, cur_pow = 0, cur_node;

    for (size_t i = 0; i < length; i++) {
        cur_pow = 0;
        cur_node = graph_edges[i].a;
        for (size_t j = 0; j < length; j++) {
            if (graph_edges[j].b == cur_node) {
                cur_pow++;
            }
        }
        if (cur_pow > max_pow) {
            max_pow = cur_pow;
            answer = cur_node;
        }
        cur_pow = 0;
        cur_node = graph_edges[i].b;
        for (size_t j = 0; j < length; j++) {
            if (graph_edges[j].b == cur_node) {
                cur_pow++;
            }
        }
        if (cur_pow > max_pow) {
            max_pow = cur_pow;
            answer = cur_node;
        }
    }
    return answer;
}

int main() {
    unsigned ans1, expected_ans1 = 5, ans2, expected_ans2 = 4;
    edge graph_edges1[4] = {
        {1, 5}, {4, 5}, {5, 2}, {3, 5}
    };
    ans1 = center(4, graph_edges1);
    if (ans1 != expected_ans1) {
        printf("Test1 failed\n");       
        return 1;
    }

    edge graph_edges2[3] = {
        {1, 4}, {4, 2}, {3, 4}
    };
    ans2 = center(3, graph_edges2);
    if (ans2 != expected_ans2) {
        printf("Test2 failed\n");
        return 1;
    }

    printf("All tests OK\n");
    return 0;
}