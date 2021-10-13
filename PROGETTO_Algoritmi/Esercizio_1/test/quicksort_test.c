#include <stdlib.h>
#include "unity.h"
#include "sorter.h"

extern int partition(void **arr, int begin, int end, CmpFunc compare);

static int *int_new(int n)
{
  int *result = (int *)malloc(sizeof(int));
  *result = n;

  return result;
}

static int compare_ints(int *obj1, int *obj2)
{
  return *obj1 - *obj2;
}

static int **create_test_array(int *values, int size)
{
  int **arr = (int **)malloc(sizeof(int *) * size);
  for (int i = 0; i < size; i++)
  {
    arr[i] = int_new(values[i]);
  }
  return arr;
}

static void free_test_array(int **array, int size)
{
  for (int i = 0; i < size; i++)
  {
    free(array[i]);
  }
  free(array);
}

static void p_begin()
{

  int **arr;
  int v[] = {1, 5, 3, 4, 2};
  int result;
  arr = create_test_array(v, 5);

  result = partition((void **)arr, 0, 4, (CmpFunc)compare_ints);
  TEST_ASSERT_EQUAL(1, *arr[0]);
  TEST_ASSERT_EQUAL(5, *arr[1]);
  TEST_ASSERT_EQUAL(3, *arr[2]);
  TEST_ASSERT_EQUAL(4, *arr[3]);
  TEST_ASSERT_EQUAL(2, *arr[4]);

  TEST_ASSERT_EQUAL(0, result);
  
  free_test_array(arr, 5);
}

static void p_middle()
{

  int **arr;
  int v[] = {3, 5, 2, 4, 1};
  int i, result;

  arr = create_test_array(v, 5);

  result = partition((void **)arr, 0, 4, (CmpFunc)compare_ints);
  TEST_ASSERT_EQUAL(2, *arr[0]);
  TEST_ASSERT_EQUAL(1, *arr[1]);
  TEST_ASSERT_EQUAL(3, *arr[2]);
  TEST_ASSERT_EQUAL(4, *arr[3]);
  TEST_ASSERT_EQUAL(5, *arr[4]);

  TEST_ASSERT_EQUAL(2, result);
  
  free_test_array(arr, 5);
}

static void p_end()
{

  int **arr;
  int v[] = {6, 5, 2, 4, 3};
  int result;

  arr = create_test_array(v, 5);

  result = partition((void **)arr, 0, 4, (CmpFunc)compare_ints);
  TEST_ASSERT_EQUAL(3, *arr[0]);
  TEST_ASSERT_EQUAL(5, *arr[1]);
  TEST_ASSERT_EQUAL(2, *arr[2]);
  TEST_ASSERT_EQUAL(4, *arr[3]);
  TEST_ASSERT_EQUAL(6, *arr[4]);

  TEST_ASSERT_EQUAL(4, result);
  
  free_test_array(arr, 5);
}

static void quicksort_empty_array()
{
  quicksort(NULL, 0, (CmpFunc)compare_ints);
}

static void quicksort_single_element_array()
{
  int **arr = (int **)malloc(sizeof(int *) * 1);
  arr[0] = int_new(1);

  quicksort((void **)arr, 1, (CmpFunc)compare_ints);

  TEST_ASSERT_EQUAL(1, *arr[0]);
  
  free_test_array(arr, 1);
}

static void quicksort_sorted_array()
{
  int **arr;
  int v[] = {1, 2, 3, 5, 6, 6, 7, 8, 8, 11, 14};
  int i;
  arr = create_test_array(v, 11);

  quicksort((void **)arr, 11, (CmpFunc)compare_ints);

  for (i = 0; i < 11; i++)
    TEST_ASSERT_EQUAL(v[i], *arr[i]);
  
  free_test_array(arr, 11);
}

static void quicksort_inverse_sorted_array()
{
  int **arr;
  int v[] = {14, 11, 8, 8, 7, 6, 6, 5, 3, 2, 1};
  int v_sorted[] = {1, 2, 3, 5, 6, 6, 7, 8, 8, 11, 14};
  int i;
  arr = create_test_array(v, 11);

  quicksort((void **)arr, 11, (CmpFunc)compare_ints);

  for (i = 0; i < 11; i++)
    TEST_ASSERT_EQUAL(v_sorted[i], *arr[i]);
  
  free_test_array(arr, 11);
}

static void quicksort_normal_array()
{

  int **arr;
  int v[] = {8, 1, 5, 6, 7, 3, 6, 8, 11, 14, 2};
  int v_sorted[] = {1, 2, 3, 5, 6, 6, 7, 8, 8, 11, 14};
  int i;
  arr = create_test_array(v, 11);

  quicksort((void **)arr, 11, (CmpFunc)compare_ints);

  for (i = 0; i < 11; i++)
    TEST_ASSERT_EQUAL(v_sorted[i], *arr[i]);
  
  free_test_array(arr, 11);
}

int main()
{
  UNITY_BEGIN();
  
  RUN_TEST(p_begin);
  RUN_TEST(p_middle);
  RUN_TEST(p_end);

  RUN_TEST(quicksort_empty_array);
  RUN_TEST(quicksort_single_element_array);
  RUN_TEST(quicksort_sorted_array);
  RUN_TEST(quicksort_inverse_sorted_array);
  RUN_TEST(quicksort_normal_array);

  UNITY_END();
}