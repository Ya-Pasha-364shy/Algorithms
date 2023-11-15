#include <stdio.h>
#include <stdlib.h>

#include "testlib.h"
/*
 * Description:
 *
 * Write a function that takes an integer as input,
 * and returns the number of bits that are equal to
 * one in the binary representation of that number.
 * You can guarantee that input is non-negative.
*/

size_t countBits(unsigned value)
{
	size_t bitsCount = 0;
	while (value > 0)
	{
		if (value % 2)
			bitsCount++;
		value /= 2;
	}
	return bitsCount;
}

int main()
{
	size_t test1 = 1;
	IS_EQUALS(countBits(4), test1);
	test1 = 5;
	IS_EQUALS(countBits(1234), test1);

	return 0;
}