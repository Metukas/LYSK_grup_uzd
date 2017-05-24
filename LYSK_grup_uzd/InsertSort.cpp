#include <omp.h>

template <class X> void sortInsert(X *arrayToSort, int arraySize)
{
	int i;
	for (i = 0; i < arraySize; i++)
	{
		X element = arrayToSort[i];
		int j;
		for (j = i; j > 0 && arrayToSort[j - 1] > element; j--)
		{
			arrayToSort[j] = arrayToSort[j - 1];
		}
		arrayToSort[j] = element;
	}
}

