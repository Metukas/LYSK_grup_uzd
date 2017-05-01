#include <iostream>
using namespace std;

template <class X> void bubble(X *items, int count)
{
	X t;

	for (int a = 1; a<count; a++)
		for (int b = count - 1; b >= a; b--)
			if (items[b - 1] > items[b]) 
			{
				t = items[b - 1];
				items[b - 1] = items[b];
				items[b] = t;
			}
}

template <class X> void sortInsert(X *arrayToSort, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		X element = arrayToSort[i];
		int j = i;
		while (j > 0 && arrayToSort[j - 1] > element)
		{
			arrayToSort[j] = arrayToSort[j - 1];
			j--;
		}
		arrayToSort[j] = element;
	}
}

