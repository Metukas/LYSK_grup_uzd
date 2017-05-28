#include <omp.h>
#include "N.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <limits>
#include <vector>
#include <assert.h>

template <class X> void sortInsert(std::vector<X> &arrayToSort)
{
	clock_t tStart = clock();
	int i, dalinimas;
	int a = omp_get_max_threads();
	int b = N / a;
	int liek = N % a;
	int kiekdalint;
	int tredas;
	double kelt;
	int *ats = new int[a];
	X *saugo = new X[(a - 1) * a];
	int *pozicija = new int[a];
	X *rodykle;
	X *didiejisk = new X[a - 1];
	X **elementai = new X*[a * a + 1];
	int tred;
	int ui = 0;
	int j;
	int spozicija = 0;
	X element;
	X t;
	X** are = new X*[a];
	for (int i = 0; i < a; ++i)
		are[i] = new X[(int)round(N / a)];
	X*** ary = new X**[a];
	for (int i = 0; i < a; ++i)
		ary[i] = new X*[2 * a];
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
			element = rodykle[i];
			for (j = i; j > 0 && rodykle[j - 1] > element; j--)
				rodykle[j] = rodykle[j - 1];
			rodykle[j] = element;
		}
	}
	kelt = (double)N / a / a;
	for (int ta = 0; ta < a; ta++)
	{
		for (int sa = 0; sa < a - 1; sa++)
		{
			if (sa == 0)
				saugo[ui] = arrayToSort[(int)kelt + pozicija[ta]];
			else
				saugo[ui] = arrayToSort[(int)round((sa + 1) * kelt) + pozicija[ta]];
			ui++;
		}
	}
	for (int wa = 1; wa < (a - 1) * a; wa++)
		for (int da = (a - 1) * a - 1; da >= wa; da--)
			if (saugo[da - 1] > saugo[da])
			{
				t = saugo[da - 1];
				saugo[da - 1] = saugo[da];
				saugo[da] = t;
			}
	ui = 0;
	kelt = (double) a - 1;
	for (int sa = 0; sa < a - 1; sa++)
	{
		if (sa == 0)
			didiejisk[sa] = saugo[(int)kelt];
		else
			didiejisk[sa] = saugo[(int)round((sa + 1) * kelt) + sa];
		ui++;
	}
	int lk = 0;
	for (int aha = 0; aha < a; aha++)
	{
		rodykle = &arrayToSort[pozicija[aha]];
		for (int asa = 0; asa < a ; asa++)
		{
			if (asa == 0)
				elementai[lk] = rodykle;
			else
				elementai[lk] = std::upper_bound(rodykle, rodykle + ats[aha] - 1, didiejisk[asa - 1]);
			lk++;
		}
	}
	elementai[lk] = &arrayToSort[N];
	lk = 0;
	for (int awa = 0; awa < 2 * a; awa++)
	{
		for (int asa = 0; asa < a; asa++)
		{
			ary[asa][awa] = elementai[lk];
			ary[asa][awa + 1] = elementai[lk + 1];
			lk++;
		}
		awa += 1;
	}
	#pragma omp parallel 
	{
		std::vector<X> vektorius;
		int ID = omp_get_thread_num();
		for (int xc = 0; xc < 2 * a; xc += 2)
		{
			for (X *uj = &ary[ID][xc][0]; uj < &ary[ID][xc + 1][0]; uj++)
				vektorius.insert(vektorius.end(), *uj);
		}
		X elementare;
		int ja;
		for (int zxcv = 0; zxcv < vektorius.size(); zxcv++)
		{
			elementare = vektorius[zxcv];
			ja = zxcv;
			while (ja > 0 && vektorius[ja - 1] > elementare)
			{
				vektorius[ja] = vektorius[ja - 1];
				ja--;
			}
			vektorius[ja] = elementare;
		}
		#pragma omp master
			std::cout << "Time taken: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << " s\n";
		#pragma omp barrier
		#pragma omp for ordered schedule(static,1)
		for (int t = 0; t < a; ++t)
		{
			assert(t == ID);
			#pragma omp ordered
			{
				for (int qwa = 0; qwa < vektorius.size(); qwa++)
					std::cout << vektorius[qwa] << " ";
			}
		}
	}
}
