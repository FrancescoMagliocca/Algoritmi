typedef int (*CmpFunc)(void*, void*);
void insertionsort(void **array, int size, CmpFunc cf);
void quicksort(void **array, int size, CmpFunc);
int partition(void **arr, int begin, int end, CmpFunc compare);
void iquicksort(void **arr, int begin, int end, CmpFunc compare);
