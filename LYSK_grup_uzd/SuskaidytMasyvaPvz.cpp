#include <iostream>
#include <omp.h>
#include <time.h>
#include <cstring>

using namespace std;

int suskaidyt()
{
	int threadNum; int size = 24;
	int* arr = (int*)malloc(size * sizeof(int));

#pragma omp parallel
	{
#pragma omp master
			threadNum = omp_get_num_threads();
	}
	//threadNum = 2;
	srand(time(NULL));
	cout << "arr[]: " << endl;
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % 100;
		cout << arr[i] << " ";
	}
	cout << endl;

	int chunkSize = size / threadNum;
	int** pointerToArrays = (int**)malloc(threadNum * sizeof(int)); //padarom tiek suskaidytų masyvu, kiek yra branduolių kompiutery
	
	for (int i = 0; i < threadNum; i++)
	{
		int offset = ((size / threadNum) * i);
		int* source = arr + offset;
		pointerToArrays[i] = (int*)malloc(chunkSize * sizeof(int));
		memcpy(pointerToArrays[i], source, chunkSize * sizeof(int)); //suskaidom masyva arr dalimis į pointerToArrays[i]
	}

	for (int i = 0; i < threadNum; i++)
	{
		cout << "Chunk Nr.: " << i << endl;
		for (int j = 0; j < chunkSize; j++)
		{
			cout << pointerToArrays[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
