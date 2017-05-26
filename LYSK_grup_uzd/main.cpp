//Lysk grupinė užduotis
/*
Užduotis: parašykite programą, lygiagrečiai rikiuojančią pateiktus duomenis įterpties (insertion) ir
skaidymo-suliejimo (merge) algoritmais.
• Programa turėtų rikiuoti bet kokio tipo objektus, kuriems gali būti apibrėžtos rikiavimo taisyklės.
◦ Jei išeina, skaičių (sveikųjų ir realiųjų) rikiavimą optimizuokite
(jų rikiavimo taisykles palaiko pati C++ kalba).
• Palyginkite algoritmų veikimą. Ar kuris nors iš jų tinkamesnis lygiagretinimui?
*/

#include "Sort.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <omp.h>

using namespace std;

#define N 100000000

int main()
{
	cout << "Hello" << endl;
	int* arr = new int[N];
	int threadNum;
#pragma omp parallel
	{
#pragma omp master
		threadNum = omp_get_num_threads();
	}

	srand(time(NULL));

	//cout << "Pries surikiavima" << endl;

	generate_list(arr, N);

	cout << endl;
	cout << endl;
	cout << endl;

	//sortInsert(arr, N);
	sortMergeParallel(arr, N, threadNum);

	cout << "Po surikiavimo int" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << endl;
	cout << endl;

	return EXIT_SUCCESS;
}
