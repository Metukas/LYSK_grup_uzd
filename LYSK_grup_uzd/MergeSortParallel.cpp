#include <cstdlib>
#include <stdio.h>
#include "Tvarka.h"
#include "Merge.h"

template <class X> void sortMergeParallel(X* data, int size, int threadNum)
{
	int n = size;

	if (threadNum > 8)
		threadNum = 8;

	//duodam atminties masyvams
	X* tmp = new X[n];

	if (threadNum <= 1)
	{
		mergesort(data, n, tmp);
		return;
	}

	threadNum = isPowerOf2(threadNum) ? threadNum : pow2RoundDown(threadNum);

	//suskirstom duomenis
	int liekana = n % threadNum;
	int chunkSize = n / threadNum;
	X** pointerToTmp = (X**)malloc(threadNum * sizeof(X*)); //padarom tiek suskaidytų laikinų masyvu, kiek yra branduolių kompiutery
	int* chunkSizes = (int*)malloc(threadNum * sizeof(int));
	int* offsets = (int*)malloc(threadNum * sizeof(int));
	for (int i = 0; i < threadNum; i++)
	{
		//int kiekdalint = liekana - i;
		int kiekdalint = i - threadNum + liekana;
		//if (kiekdalint > 0)
		if (kiekdalint >= 0)
			chunkSizes[i] = chunkSize + 1;
		else
			chunkSizes[i] = chunkSize;

		if (i == 0)
			offsets[0] = 0;
		else if (i == 1)
			offsets[1] = chunkSizes[0];
		else if (i == 2)
			offsets[2] = chunkSizes[0] + chunkSizes[1];
		else
			offsets[i] = offsets[i - 1] + chunkSizes[i - 1];

		//kiekvienam threadui duodam po atskirą laikiną masyvą, kad nebūtų data racing.
		pointerToTmp[i] = (X*)malloc(chunkSizes[i] * sizeof(X));
	}

#pragma omp parallel for
	for (int i = 0; i < threadNum; i++)
	{
		X* source = data + offsets[i];
		mergesort(source, chunkSizes[i], pointerToTmp[i]);
	}

	delete[] pointerToTmp;

	//padarom paskutinį merge sortą. (nesugalvojau, kaip geriau padaryti, todėl tiesiog harcodinau kelis case ¯\_(ツ)_/¯)
	switch (threadNum)
	{
	case 2: //n=2
		merge(data, n, tmp);
		break;
	case 4: //n=4
		merge(data, chunkSizes[0] + chunkSizes[1], tmp);
		merge(data + offsets[2], chunkSizes[2] + chunkSizes[3], tmp);
		merge(data, n, tmp);
		break;
	case 8: //n=8
		merge(data, chunkSizes[0] + chunkSizes[1], tmp);
		merge(data + offsets[2], chunkSizes[2] + chunkSizes[3], tmp);
		merge(data + offsets[4], chunkSizes[4] + chunkSizes[5], tmp);
		merge(data + offsets[6], chunkSizes[6] + chunkSizes[7], tmp);
		merge(data, chunkSizes[0] + chunkSizes[1] + chunkSizes[2] + chunkSizes[3], tmp);
		merge(data + offsets[4], chunkSizes[4] + chunkSizes[5] + chunkSizes[6] + chunkSizes[7], tmp);
		merge(data, n, tmp);
		break;
	}
}

template <class X> void  mergesort(X * data, int n, X * tmp)
{
	if (n < 2) return;

	mergesort(data, n / 2, tmp);
	mergesort(data + (n / 2), n - (n / 2), tmp);

	merge(data, n, tmp);
}

template <class X> void  merge(X * data, int n, X * tmp) // teisingai sumergina, kai masyvo pradžioje yra tiek pat arba mažiau elementų negu pabaigoje.
{
	int i = 0;
	int j = n / 2;
	int ti = 0;

	while (i < n / 2 && j < n)
	{
		if (didejimoTvarka ? data[i] < data[j] : data[i] > data[j])
		{
			tmp[ti] = data[i];
			ti++; i++;
		}
		else
		{
			tmp[ti] = data[j];
			ti++; j++;
		}
	}
	while (i < n / 2)
	{
		tmp[ti] = data[i];
		ti++; i++;
	}
	while (j < n)
	{
		tmp[ti] = data[j];
		ti++; j++;
	}
	memcpy(data, tmp, n * sizeof(X));
}