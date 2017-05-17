#include <iostream>

template <class X> X getMax(X x, X y)
{
	return x > y ? x : y;
}
template <class X> X getMin(X x, X y)
{
	return x < y ? x : y;
}

template <class X> void mergeSortHelper(X *input, int left, int right, X *tempArray)
{
	if (right == left + 1)
	{
		return;
	}
	else
	{
		int i = 0;
		int length = right - left;
		int midpoint_distance = length / 2;

		int l = left, r = left + midpoint_distance;

		mergeSortHelper(input, left, left + midpoint_distance, tempArray);
		mergeSortHelper(input, left + midpoint_distance, right, tempArray);

		for (i = 0; i < length; i++)
		{
			if (l < left + midpoint_distance &&
				(r == right || getMax(input[l], input[r]) == input[l]))
			{
				tempArray[i] = input[l];
				l++;
			}
			else
			{
				tempArray[i] = input[r];
				r++;
			}
		}
		for (i = left; i < right; i++)
		{
			input[i] = tempArray[i - left];
		}
	}
}

template <class X> int sortMerge(X *input, int size)
{
	X *tempArray = (X *)malloc(size * sizeof(X));
	if (tempArray != NULL)
	{
		mergeSortHelper(input, 0, size, tempArray);
		free(tempArray);
		return 1;
	}
	else
	{
		return 0;
	}
}