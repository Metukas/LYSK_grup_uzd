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

