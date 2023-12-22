#include <string.h>

#define COUNTS_SIZE 128

//  assign char counts to the provided pre-allocated array
//  pre-existing values in array aren't guaranteed to be 0
//  from test string: "aaa", counts['a'] should be == to 3

void count(const char *string, unsigned counts[COUNTS_SIZE]) {
	for (size_t it = 0; it < COUNTS_SIZE; it++)
		counts[it] = 0;

	for (size_t i = 0; i < strlen(string); i++)
	{
		if (counts[string[i]]) continue;

		size_t counter = 0;
		for (size_t j = 0; j < strlen(string); j++)
		{
			if (string[i] == string[j])
				++counter;
		}
		counts[string[i]] = counter;
	}
}