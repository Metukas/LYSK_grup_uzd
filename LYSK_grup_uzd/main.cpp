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

using namespace std;

#define N 100

int main()
{
	cout << "Hello" << endl;
	int arr[N];
	int arrfloat[N];
	srand(time(NULL));

	cout << sizeof(arr) / sizeof(int) << endl;

	cout << "Pries surikiavima" << endl;
	for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		arr[i] = rand()  % 51;
		arrfloat[i] = rand() % 100;
		cout << arr[i] << " ";
	}

	cout << endl;
	cout << endl;
	cout << endl;
	//sortBubble(arr, N);
	//sortInsert(arr, N);
	unsigned char b;
	cin >> b;
	if(b % 2 == 0)
		sortMerge(arr, N);
	else
		sortMerge(arrfloat, N);


	cout << "Po surikiavimo int" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "Po surikiavimo float" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << arrfloat[i] << " ";
	}
	cout << endl;

	return EXIT_SUCCESS;
}
/*
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>

int main()
{
	using namespace nana;

	//Define a form.
	form fm;

	//Define a label and display a text.
	label lab{ fm, "Hello, <bold blue size=16>Nana C++ Library</>" };
	lab.format(true);

	//Define a button and answer the click event.
	button btn{ fm, "Quit" };
	btn.events().click([&fm]
	{
		fm.close();
	});

	//Layout management
	fm.div("vert <><<><weight=80% text><>><><weight=24<><button><>><>");
	fm["text"] << lab;
	fm["button"] << btn;
	fm.collocate();

	//Show the form
	fm.show();

	//Start to event loop process, it blocks until the form is closed.
	exec();
}
*/