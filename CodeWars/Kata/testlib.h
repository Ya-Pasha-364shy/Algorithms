#include <stdio.h>
#include <stdbool.h>

#define IS_EQUALS(x, y) \
	if (x == y) \
		printf("Test succeeded !\n"); \
	else \
		printf("Received %ld, but expected: %ld\n", x, y);

#define IS_ARRS_EQUALS(x, y, n) \
	bool arrays_are_equals = true; \
	for (int i = 0; i < n; i++) { \
		if (x[i] != y[i]) { \
			arrays_are_equals = false; \
			break; \
		} \
	}
