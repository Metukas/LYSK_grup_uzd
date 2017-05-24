// Toliauto programa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omp.h"
#include <iostream>

using namespace std;

#define MAX_SIZE 100000000000


void generate_list(int * x, int n) { //susigeneruojame sarasa skaiciu kuriuos rikiuosime
	int i, j, t;
	for (i = 0; i < n; i++)
		x[i] = i;
	for (i = 0; i < n; i++) {
		j = rand() % n;
		t = x[i];
		x[i] = x[j];
		x[j] = t;
	}
}

void print_list(int * x, int n) { //atspausdiname skaiciu sarasa
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", x[i]);
	}
}

void merge(int * X, int n, int * tmp) { // veikia merge algortimas
	int i = 0;
	int j = n / 2;
	int ti = 0;

	while (i<n / 2 && j<n) {
		if (X[i] < X[j]) {
			tmp[ti] = X[i];
			ti++; i++;
		}
		else {
			tmp[ti] = X[j];
			ti++; j++;
		}
	}
	while (i<n / 2) { 
		tmp[ti] = X[i];
		ti++; i++;
	}
	while (j<n) { 
		tmp[ti] = X[j];
		ti++; j++;
	}
	memcpy(X, tmp, n * sizeof(int));

} 

//void mergesort(int * X, int n, int * tmp)
//{
//	if (n < 2) return;
//
//#pragma omp parallel sections
//	{
//#pragma omp section
//	mergesort(X, n / 2, tmp);
//
//#pragma omp section
//	mergesort(X + (n / 2), n - (n / 2), tmp);
//	}
//#pragma omp taskwait
//
//	// susortina i merge lista
//	merge(X, n, tmp);
//}


void mergesort(int * X, int n, int * tmp)
{
	if (n < 2) return;

	mergesort(X, n / 2, tmp);

	// susortina i merge lista
	merge(X, n, tmp);
}



int main()
{
	int n = 100000000;
	double start, stop;
	int threadNum;
#pragma omp parallel
	{
#pragma omp master
		threadNum = omp_get_num_threads();
	}
	//omp_set_num_threads(4);

	//int data[MAX_SIZE], tmp[MAX_SIZE];
	int *data = (int *)malloc(n * sizeof(int));
	int *tmp = (int *)malloc(n * sizeof(int));

	cout << threadNum << endl << endl;
	cout << "generuojamas listas... \n";
	generate_list(data, n);
	cout << "baigta generuoti lista \n";

	int chunkSize = n / threadNum;
	int** pointerToArrays = (int**)malloc(threadNum * sizeof(int)); //padarom tiek suskaidytø masyvu, kiek yra branduoliø kompiutery

	for (int i = 0; i < threadNum; i++)
	{
		int offset = ((n / threadNum) * i);
		int* source = data + offset;
		pointerToArrays[i] = (int*)malloc(chunkSize * sizeof(int));
		memcpy(pointerToArrays[i], source, chunkSize * sizeof(int)); //suskaidom masyvà arr á dalis á pointerToArrays[i]
	}

	for (int ptrNr = 0; ptrNr < threadNum; ptrNr++)
	{
		for (int i = 0; i < chunkSize; i++)
		{
			//cout << pointerToArrays[ptrNr][i] << " ";
		}
		//cout << endl << endl << endl << endl;
		cout << ":D \n";
	}

	//printf("List Before Sorting...\n");
	//print_list(data, n);
	start = omp_get_wtime();

	cout << "rikiuojama... \n";
#pragma omp parallel for
	for (int i = 0; i < threadNum; i++)
	{
		merge(pointerToArrays[i], chunkSize, tmp);
	}
	stop = omp_get_wtime();

	//printf("\nList After Sorting...\n");
	//print_list(data, n);
	cout << "baigta rikiuoti \n";
	printf("\nTime to isrikiuoti: %g\n", stop - start);
}