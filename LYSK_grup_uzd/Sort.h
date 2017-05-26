template <class X> void sortInsert(X *arrayToSort, int arraySize);
template <class X> void sortMergeParallel(X* data, int size, int threadNum);

bool isPowerOf2(int num);
int pow2RoundUp(int x);
int pow2RoundDown(int x);
void generateList(int * x, int n);
void printList(int * x, int n);


#include "InsertSort.cpp"
#include "MergeSortParallel.cpp"