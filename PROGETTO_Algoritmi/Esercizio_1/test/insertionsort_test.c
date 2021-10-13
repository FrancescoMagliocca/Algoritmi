#include <stdlib.h>
#include "unity.h"
#include "sorter.h"

static int *int_new(int n) {
  int *result = (int *)malloc(sizeof(int));
  *result = n;

  return result;
}

static int compare_ints(int *obj1, int *obj2) {
  return *obj1 - *obj2;
}

static int **create_test_array(int *values, int size) {
  int **arr = (int**) malloc(sizeof(int *) * size);
  for (int i = 0; i < size; i++) {
    arr[i] = int_new(values[i]);
  }
  return arr;
}



static void empty_array() {
  insertionsort(NULL , 0, (CmpFunc)compare_ints);
  TEST_ASSERT_TRUE(1);
}

static void free_test_array(int **array, int size) {
  for (int i = 0; i < size; i++)
    free(array[i]);
  free(array);
}

static void ordered_array() {
  int **a;
  int v[] = {1, 4, 6, 7, 12, 17, 23};
  a = create_test_array(v, 7);

  insertionsort((void**)a , 7, (CmpFunc)compare_ints);

  TEST_ASSERT_EQUAL(1, *a[0]);
  TEST_ASSERT_EQUAL(4, *a[1]);
  TEST_ASSERT_EQUAL(6, *a[2]);
  TEST_ASSERT_EQUAL(7, *a[3]);
  TEST_ASSERT_EQUAL(12, *a[4]);
  TEST_ASSERT_EQUAL(17, *a[5]);
  TEST_ASSERT_EQUAL(23, *a[6]);

  free_test_array(a, 7);
}

static void inv_ordered_array() {
  int **a;
  int v[] = {23, 17, 12, 7, 6, 4, 1};
  a = create_test_array(v, 7);

  insertionsort((void**)a , 7, (CmpFunc)compare_ints);

  TEST_ASSERT_EQUAL(1, *a[0]);
  TEST_ASSERT_EQUAL(4, *a[1]);
  TEST_ASSERT_EQUAL(6, *a[2]);
  TEST_ASSERT_EQUAL(7, *a[3]);
  TEST_ASSERT_EQUAL(12, *a[4]);
  TEST_ASSERT_EQUAL(17, *a[5]);
  TEST_ASSERT_EQUAL(23, *a[6]);

  free_test_array(a, 7);
}

static void unordered_array() {
  int **a;
  int v[] = {12, 4, 17, 23, 1, 6, 7};
  a = create_test_array(v, 7);

  insertionsort((void**)a , 7, (CmpFunc)compare_ints);

  TEST_ASSERT_EQUAL(1, *a[0]);
  TEST_ASSERT_EQUAL(4, *a[1]);
  TEST_ASSERT_EQUAL(6, *a[2]);
  TEST_ASSERT_EQUAL(7, *a[3]);
  TEST_ASSERT_EQUAL(12, *a[4]);
  TEST_ASSERT_EQUAL(17, *a[5]);
  TEST_ASSERT_EQUAL(23, *a[6]);

  free_test_array(a, 7);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(empty_array);
  RUN_TEST(ordered_array);
  RUN_TEST(inv_ordered_array);
  RUN_TEST(unordered_array);

  UNITY_END();
}