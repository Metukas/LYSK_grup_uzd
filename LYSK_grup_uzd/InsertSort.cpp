#include "Tvarka.h"
#include <omp.h>
#include <iostream>

template <class X> void finalMerge(X* data, int* chunkSizes, int* offsets, X* tmp, int size, int threadNumb);

template <class X> void sortInsert(X *data, int size, int threadNum)
{
	int n = size;
	if (threadNum > 8)
		threadNum = 8;

	int chunkSize = size / threadNum;
	int liek = size % threadNum;
	int kiekdalint;
	int tredas;
	int *chunkSizes = new int[threadNum];
	int *offsets = new int[threadNum];
	int *rodykle;
	int tred;
	for (int i = 0; i < threadNum; i++)
	{
		tredas = i;
		kiekdalint = liek - tredas;
		if (kiekdalint > 0)
			chunkSizes[i] = chunkSize + 1;
		else
			chunkSizes[i] = chunkSize;
	}
	for (int i = 0; i < threadNum; i++)
	{
		if (i == 0)
			offsets[0] = 0;
		else if (i == 1)
			offsets[1] = chunkSizes[0];
		else if (i == 2)
			offsets[2] = chunkSizes[0] + chunkSizes[1];
		else
			offsets[i] = offsets[i - 1] + chunkSizes[i - 1];
	}
#pragma omp parallel num_threads(threadNum)
	{
		tred = omp_get_thread_num();
		rodykle = &data[offsets[tred]];
		for (int i = 0; i < chunkSizes[tred]; i++)
		{
			X element = rodykle[i];
			int j;
			for (j = i; j > 0 && (didejimoTvarka ? rodykle[j - 1] > element : rodykle[j - 1] < element); j--)
			{
				rodykle[j] = rodykle[j - 1];
			}
			rodykle[j] = element;
		}
	}

	X* tmp = new X[n];
	
	//¯\_(ツ)_/¯
	finalMerge(data, chunkSizes, offsets, tmp, size, threadNum);
}
