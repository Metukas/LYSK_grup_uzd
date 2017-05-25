#include <omp.h>
#include "N.h"
#include <iostream>
#include "N.h"



template <class X> void sortInsert(X *arrayToSort)
{
	int i, dalinimas;
	/*int e;
	int k = 0;
	X** a = new X*[omp_get_max_threads() + 1];
	for (int e = 0; e < omp_get_max_threads() + 1; ++e)
	a[e] = new int[N / (omp_get_max_threads() + 1)];
	for (int op1 = 0; op1 < omp_get_max_threads() + 1; op1++)
	{
	for (int op = 0; op < N / omp_get_max_threads(); op++, k++)
	a[op1][op] = arrayToSort[k];
	}
	for (int op = 0; op < N / omp_get_max_threads(); op++)
	cout << a[0][op] << " ";
	cout << endl;
	for (int op = 0; op < N / omp_get_max_threads(); op++)
	cout << a[1][op] << " ";*/
	/*int *a;
	a = &arrayToSort[0] + omp_get_thread_num()*N/omp_get_max_threads();
	cout << a[0];*/
	int a = omp_get_max_threads();
	int b = N / a;
	int liek = N % a;
	int kiekdalint;
	int tredas;
	int *ats = new int[a];
	int *pozicija = new int [a];
	int *rodykle;
	int tred;
	for (int ra = 0; ra < a; ra++)
	{
		tredas = ra;
		kiekdalint = liek - tredas;
		if (kiekdalint > 0)
			ats[ra] = b + 1;
		else
			ats[ra] = b;
	}
	for (int ra = 0; ra < a; ra++)
	{
		if (ra == 0)
			pozicija[0] = 0;
		else if (ra == 1)
			pozicija[1] = ats[0];
		else if (ra == 2)
			pozicija[2] = ats[0] + ats[1];
		else
			pozicija[ra] = pozicija[ra - 1] + ats[ra - 1];
	}
	#pragma omp parallel
	{
		tred = omp_get_thread_num();
		rodykle = &arrayToSort[pozicija[tred]];
		for (i = 0; i < ats[tred]; i++)
		{
			X element = rodykle[i];
			int j;
			for (j = i; j > 0 && rodykle[j - 1] > element; j--)
			{
				rodykle[j] = rodykle[j - 1];
			}
			rodykle[j] = element;
		}
	}
}
