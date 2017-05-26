#include <cstdlib>
#include <stdio.h>

bool isPowerOf2(int num)
{
	if (num <= 0)
		return false;

	return (num & (num - 1)) == 0;
}

int pow2RoundUp(int x)
{
	if (x < 0)
		return 0;

	--x;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x + 1;
}

int pow2RoundDown(int x)
{
	if (x < 0)
		return 0;

	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	return x - (x >> 1);
}

void generateList(int * x, int n)
{
	int i, j, t;
	for (i = 0; i < n; i++)
		x[i] = i;
	for (i = 0; i < n; i++) {
		j = rand() % n;
		t = x[i];
		x[i] = x[j];
		x[j] = t;
	}
}

void printList(int * x, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", x[i]);
	}
}
