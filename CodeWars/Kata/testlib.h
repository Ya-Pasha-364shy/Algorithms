#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define IS_EQUALS(x, y) \
	if (x == y) \
		printf("Test succeeded !\n"); \
	else \
		printf("Received %ld, but expected: %ld\n", x, y);

#define IS_ARRS_EQUALS(x, y, n) { \
	bool arrays_are_equals = true; \
	for (int i = 0; i < n; i++) { \
		if (x[i] != y[i]) { \
			arrays_are_equals = false; \
			break; \
		} \
	}\
	if (arrays_are_equals) { \
		printf("[EQ] Arrays %s and %s are equals !\n", #x, #y); \
	} else { \
		printf("[NEQ] Arrays %s and %s ARE NOT equals !\n", #x, #y); \
	} \
}

#define IS_STR_EQUALS(dst, src, size) { \
	if (0 == strncmp(dst, src, size)) \
		printf("[EQ] strokes are equals !\n"); \
	\
	else \
		printf("[NEQ] strokes aren't equals !!!\n"); \
}