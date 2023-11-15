#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "testlib.h"

int ** multiplication_table(int n)
{
	size_t row_col_size = sizeof(int) * n;
	int ** multiplication_mtx = (int **)malloc(sizeof(int *) * n);
	for (int counter = 0; counter < n; counter++)
	{
		multiplication_mtx[counter] = (int *)malloc(row_col_size);
		multiplication_mtx[0][counter] = counter + 1;
	}

	int counter = 1;
	while (counter < n)
	{
		for (int array_cnt = 0, multiplicator = counter + 1; array_cnt < n; array_cnt++)
			multiplication_mtx[counter][array_cnt] = (array_cnt + 1) * multiplicator;
		++counter;
	}

	return multiplication_mtx;
}

int main()
{
	int n = 5;
	int ** multiplication_mtx = multiplication_table(n);
	for (size_t i = 0; i < n; i++)
	{
		free(multiplication_mtx[i]);
	}
	free(multiplication_mtx);
}