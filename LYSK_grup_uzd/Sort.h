template <class X> void sortInsert(X *arrayToSort, int arraySize);
template <class X> int sortMerge(X *input, int size);
template <class X> void sortMergeParallel(X* data, int size, int threadNum);

bool isPowerOf2(int num);
int pow2RoundUp(int x);
int pow2RoundDown(int x);
void generate_list(int * x, int n);
void print_list(int * x, int n);

#include "InsertSort.cpp"
#include "MergeSort.cpp"
#include "MergeSortParallel.cpp"