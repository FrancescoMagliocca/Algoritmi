#include "../include/lib3.h"
#include "../Resources/C/Unity/unity.h"
#include "../Resources/C/Unity/unity_internals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE    5

static int* array_int(int n){
  int* result=(int*)malloc(sizeof(int));
  *result=n;
  return result;
}

static int compare_function(char *obj1, char *obj2){
  return strcmp(obj1,obj2);
}

static int hash(char *key){
  int i=0;
  for(; *key!='\0';key++)
    i+=*key;
  return i%MAP_SIZE;
}

static void empty_test(){
  Hashmap* hm=hashmap_create(0, (hashFunction)hash, (hashCmp)compare_function);

  TEST_ASSERT_EQUAL(1, hashmap_empty(hm));
  TEST_ASSERT_EQUAL(0, hashmap_size(hm));
  TEST_ASSERT_EQUAL(0, hashmap_capacity(hm));
}

void insert_and_get_test(){
  Hashmap* hm=hashmap_create(MAP_SIZE, (hashFunction)hash, (hashCmp)compare_function);

  char* keys[]={"p1","p2","p3"};
  char* values[]={array_int(5),array_int(7),array_int(9)};

  hashmap_insert(hm, keys[0], values[0]);
  hashmap_insert(hm, keys[1], values[1]);
  hashmap_insert(hm, keys[2], values[2]);

  TEST_ASSERT_EQUAL(1, hashmap_contain_key(hm, keys[0]));
  TEST_ASSERT_EQUAL(1, hashmap_contain_key(hm, keys[1]));
  TEST_ASSERT_EQUAL(1, hashmap_contain_key(hm, keys[2]));

  TEST_ASSERT_EQUAL(5, *(int*)hashmap_get_value(hm,keys[0]));
  TEST_ASSERT_EQUAL(3, *(int*)hashmap_get_value(hm,keys[0]));
    
  hashmap_free(hm);
}

static void delete_test(){
  Hashmap* hm=hashmap_create(MAP_SIZE, (hashFunction)hash, (hashCmp)compare_function);
  char* keys[]={"p1","p2","p3"};
  char* values[]={array_int(5),array_int(7),array_int(9)};

  hashmap_insert(hm, keys[0], values[0]);
  hashmap_insert(hm, keys[1], values[1]);
  hashmap_insert(hm, keys[2], values[2]);
  hashmap_delete_key(hm, keys[1]);

  TEST_ASSERT_EQUAL(0, hashmap_contain_key(hm,keys[1]));
  TEST_ASSERT_EQUAL(2, hashmap_size(hm));

  hashmap_free(hm);
}

static void flush_test(){
  Hashmap* hm=hashmap_create(MAP_SIZE, (hashFunction)hash, (hashCmp)compare_function);

  char* keys[]={"p1","p2","p3"};
  char* values[]={array_int(5),array_int(7),array_int(9)};

  hashmap_insert(hm, keys[0], values[0]);
  hashmap_insert(hm, keys[1], values[1]);
  hashmap_insert(hm, keys[2], values[2]);
  hashmap_flush(hm);

  TEST_ASSERT_EQUAL(0, hashmap_contain_key(hm,keys[0]));
  TEST_ASSERT_EQUAL(0, hashmap_contain_key(hm,keys[1]));
  TEST_ASSERT_EQUAL(0, hashmap_contain_key(hm,keys[2]));

  hashmap_free(hm);
}


int main(int argc, char *argv[]){
  UNITY_BEGIN();
  RUN_TEST(empty_test);
  RUN_TEST(insert_and_get_test);
  RUN_TEST(delete_test);
  RUN_TEST(flush_test);
  UNITY_END();
}
