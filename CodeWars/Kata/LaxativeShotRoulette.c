#include <stdio.h>
#include <stdlib.h>

#include "testlib.h"

/*
 * Description
 *
 * Peter enjoys taking risks, and this time he has decided to take it up a notch!
 *
 * Peter asks his local barman to pour him n shots,
 * after which Peter then puts laxatives in x of them.
 * He then turns around and lets the barman shuffle the shots.
 * Peter approaches the shots and drinks a of them one at a time.
 * Just one shot is enough to give Peter a runny tummy.
 * What is the probability that Peter doesn't need to run to the loo?
 *
*/

int factorial(int n)
{
	if (n <= 0)
	{
		return 1;
	}
	else
	{
		return n * factorial(n-1);
	}
}

/* @brief
 * n - The total number of shots.
 * x - The number of laxative laden shots.
 * a - The number of shots that Peter drinks.
 * return the probability that Peter won't have the trots after drinking.
 * n will always be greater than x, and a will always be less than n.
*/
double getChance(int n, int x, int a)
{
	double tmp_n = factorial(n), tmp2 = factorial(n-a), tmp3 = factorial(a);
	double c1 = tmp_n/(tmp2 * tmp3);
	double c2 = factorial(a)/(factorial(a-x) * factorial(x));
	double result = 1 - (c2/c1);

	return result;
}

int main()
{
	IS_EQUALS(getChance(2, 1, 1), 0.5);
	IS_EQUALS(getChance(4, 1, 3), 0.25);

	return 0;
}
