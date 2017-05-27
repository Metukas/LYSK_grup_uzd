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
#include "N.h"

using namespace std;


int main()
{
	cout << "Hello" << endl;
	int arr[N];
	srand(time(NULL));

	cout << sizeof(arr) / sizeof(int) << endl;

	cout << "Pries surikiavima" << endl;
	for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		arr[i] = rand()  % 51;
		//cout << arr[i] << " ";
	}

	cout << endl;
	cout << endl;
	cout << endl;

	//sortBubble(arr, N);
	sortInsert(arr);
	//sortMerge(arr, N);

	cout << "Po surikiavimo" << endl;
	/*for (int i = 0; i < N; i++)
	{
		cout << arr[i] << " ";
	}*/
	
	cout << endl;

	return EXIT_SUCCESS;
}