#include <iostream>

int max(int x, int y)
{
	if (x < y)
	{
		return x;
	}
	else
	{
		return y;
	}
}

void merge_helper(int *input, int left, int right, int *tempArray)
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

		merge_helper(input, left, left + midpoint_distance, tempArray);
		merge_helper(input, left + midpoint_distance, right, tempArray);

		for (i = 0; i < length; i++)
		{
			if (l < left + midpoint_distance &&
				(r == right || max(input[l], input[r]) == input[l]))
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

int mergeSort(int *input, int size)
{
	int *tempArray = (int *)malloc(size * sizeof(int));
	if (tempArray != NULL)
	{
		merge_helper(input, 0, size, tempArray);
		free(tempArray);
		return 1;
	}
	else
	{
		return 0;
	}
}