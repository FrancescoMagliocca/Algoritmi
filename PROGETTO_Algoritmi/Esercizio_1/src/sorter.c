#include <stdio.h>
#include "sorter.h"


void insertionsort(void **array, int size, CmpFunc cf){
  int i, j;
  void *temp;
  for(i = 1; i < size; i++){
    for(j = i; j > 0 && cf(array[j - 1], array[j]) > 0; j--){
      temp = array[j - 1];
      array[j - 1] = array[j];
      array[j] = temp;
    }
  }
}

void quicksort(void **arr, int size, CmpFunc compare)
{
  iquicksort(arr, 0, size - 1, compare);
}

void iquicksort(void **arr, int begin, int end, CmpFunc compare)
{
  int p = 0;
  if (end > begin)
    p = partition(arr, begin, end, compare);
  if (p > begin + 1)
    iquicksort(arr, begin, p - 1, compare);
  if (p < end - 1)
    iquicksort(arr, p + 1, end, compare);
}

int partition(void **arr, int begin, int end, CmpFunc compare)//prende un mid e mette a sx i sui più piccoli e li ordina e i suoi più grandi a dx
{
  int i = begin + 1, j = end;
  while (i <= j)
  {
    if (compare(arr[i], arr[begin]) <= 0)
    {
      i += 1;
    }
    else if (compare(arr[j], arr[begin]) > 0)
      j = j - 1;
    else
    {
      void *temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
      i += 1;
      j -= 1;
    }
  }
  void *temp = arr[begin];
  arr[begin] = arr[j];
  arr[j] = temp;
  return j;
}