#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "testlib.h"

/*
 * Description:
 * 
 * Write a simple parser that will parse and run Deadfish.
 *
 * Deadfish has 4 commands, each 1 character long: 
 * `i` increments the value (initially 0)
 * `d` decrements the value
 * `s` squares the value
 * `o` outputs the value into the return array
 *
 * Invalid characters should be ignored.
*/

int * parse(const char * program)
{
	int initial_value = 0;
	int * array = NULL;
	size_t size_of_array = 1, cur_counter = 0;

	size_t size_of_prog = strlen(program);
	for (size_t i = 0; i < size_of_prog; i++)
		if (program[i] == 'o') ++size_of_array;

	array = (int *)calloc(size_of_array, sizeof(int));

	// main loop
	while (*program != 0)
	{
		switch (*program)
		{
			case 'i':
			{
				initial_value++;
				break;
			}
			case 'd':
			{
				initial_value--;
				break;
			}
			case 's':
			{
				initial_value *= initial_value;
				break;
			}
			case 'o':
			{
				array[cur_counter++] = initial_value;
				break;
			}
		}
		++program;
	}
	return array;
}

int main(void)
{
	int expected_array[] = {8, 64};
	int * result_array = parse("iiisdoso");
	IS_ARRS_EQUALS(result_array, expected_array, 2);
	free(result_array);

	return 0;
}