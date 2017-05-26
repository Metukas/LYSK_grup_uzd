//Lysk grupinė užduotis
/*
Užduotis: parašykite programą, lygiagrečiai rikiuojančią pateiktus duomenis įterpties (insertion) ir
skaidymo-suliejimo (merge) algoritmais.
• Programa turėtų rikiuoti bet kokio tipo objektus, kuriems gali būti apibrėžtos rikiavimo taisyklės.
◦ Jei išeina, skaičių (sveikųjų ir realiųjų) rikiavimą optimizuokite
(jų rikiavimo taisykles palaiko pati C++ kalba).
• Palyginkite algoritmų veikimą. Ar kuris nors iš jų tinkamesnis lygiagretinimui?
*/

#include <typeinfo>
#include "Sort.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <omp.h>
#include "Tvarka.h"

using namespace std;

bool didejimoTvarka;

#define N 100000000

int main()
{
	cout << "Hello" << endl;
	didejimoTvarka = true;

	int* arr = new int[N];
	int threadNum;
	generateList(arr, N);

#pragma omp parallel
	{
#pragma omp master
		threadNum = omp_get_num_threads();
	}

	//cout << "Pries surikiavima" << endl;
	//printList(arr, N);

	cout << "Thread Num: " << threadNum << endl;

	cout << "rikiuojama..." << endl;
	clock_t tStart = clock();
	//sortInsert(arr, N);
	sortMergeParallel(arr, N, threadNum);
	cout << "surikuota" << endl;
	printf("Is viso praejo laiko: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	printList(arr, N);

	return EXIT_SUCCESS;
}