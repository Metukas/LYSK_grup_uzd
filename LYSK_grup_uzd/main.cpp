#include "Sort.h"
#include <iostream>
#include <time.h>
#include <vector>
#include "sortTemplate.cpp"

using namespace std;

#define N 100

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
		cout << arr[i] << " ";
	}

	cout << endl;
	cout << endl;
	cout << endl;

	//bubble(arr, N);
	sortInsert(arr, N);

	cout << "Po surikiavimo" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	return EXIT_SUCCESS;
}