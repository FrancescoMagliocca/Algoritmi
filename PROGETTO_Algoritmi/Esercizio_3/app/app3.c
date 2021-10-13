#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/lib3.h"

#define ERROR_EXIT_CODE 1

#define MAP_SIZE      6321078
#define ARRAY_SIZE    6321078
#define KEYS_SIZE     10000000

typedef struct{
  int field1;
  int field2;
}Record;

int compare_field(int* obj1, int* obj2){
  return *obj1-*obj2;
} 

int hash(int *key){//la chiave 
  return *key%MAP_SIZE;
}

void swap(Record* rec1, Record* rec2){
  Record temp=*rec1;
  *rec1=*rec2;
  *rec2=temp;
}

void three_way_partition(Record* array, int lo, int hi, int* i, int* j){
  int fIndex=lo, sIndex=lo, tIndex=hi;
  Record pivot=array[fIndex];
  while (sIndex <= tIndex) {
    if(array[sIndex].field1 < pivot.field1 ) {
    swap(&array[fIndex], &array[sIndex]);
    fIndex++; 
    sIndex++;
    }
    else if(array[sIndex].field1 > pivot.field1) {
      swap(&array[sIndex], &array[tIndex]);
      tIndex--;
    }
    else { 
      sIndex++;
    }
  }
  *i = fIndex;
  *j = sIndex;
}

void quick_sort(Record *array, int lo, int hi) {//ordina l'array in ordine crescente
  if(lo < hi) {
    int left, right;
    three_way_partition(array, lo, hi, &left, &right);

    quick_sort(array, lo, left-1);
    quick_sort(array, right, hi);
    }
}

int binary_search(Record array[], int left, int right, int x) { 
  if (right >= left) { 
    int mid = left + (right - left) / 2; 
    
    if (array[mid].field1 == x) 
      return mid; 
    
    if (array[mid].field1 > x) 
      return binary_search(array, left, mid - 1, x); 
    
    return binary_search(array, mid + 1, right, x); 
  } 
    
  return -1; 
} 

Record* array_load(char const* path, int max_record){
  FILE *file=fopen(path,"r");
  Record* array=malloc(sizeof(Record)*max_record);
  int i=0;

  while(!feof(file)){
    int n=fscanf(file, "%d,%d", &array[i].field1, &array[i].field2);
      if(n!=2){
        if(feof(file))
           continue;
        printf("Error while reading file\n");
        exit(ERROR_EXIT_CODE);
      }
    i++;
  }
  fclose(file);
  return array; 
}

Hashmap* map_load(char const* path, int max_record, hashFunction hash, hashCmp compare){
  FILE *file=fopen(path,"r");//apre il file in lettura
  Hashmap* hm;//puntatore alla hashmap

  int *key, *val;
  hm=hashmap_create(max_record, hash, compare);

  while(!feof(file)){//fino a quando non si trova alla fine del file
    key=malloc(sizeof(int));
    val=malloc(sizeof(int));//alloco spazio per i 2 interi
     
    int n=fscanf(file, "%d,%d", key, val);//primo valore a key e secondo a val
    if(n!=2){
      if(feof(file))
        continue;
      printf("Error while readind file\n");
      exit(ERROR_EXIT_CODE);
    }
    hashmap_insert(hm, key, val);//inserisce le chiavi e il valore nella hashmap
  } 
  fclose(file);
  return hm;
}

void test_array(int*  keys){
  clock_t start, end;
  int count=0;
  double t1, t_total;
    
  start=clock();
  Record* array=array_load("../hashes.csv", ARRAY_SIZE);//carica l'array
  quick_sort(array, 0, ARRAY_SIZE);
  end=clock();
  t1=(double)(end-start)/CLOCKS_PER_SEC;
  t_total=t1;
  printf("Static array loaded in %f seconds\n", t1);

  start=clock();
  for(int i=0; i<KEYS_SIZE; i++) {
    if(binary_search(array, 0, ARRAY_SIZE-1, keys[i])!=-1)//fa la ricerca scorrendo l'array in modo dicotomico
      count++; //conta le chiavi recuperate
  }
  end=clock();
  t1=(double)(end-start)/CLOCKS_PER_SEC;
  t_total+=t1;
  printf("Retrieved %d elements in %f seconds.\n", count, t1);
  printf("Static array time: %f seconds\n", t_total);

  free(array);
}

void test_hashmap(int*  keys){
  clock_t start, end;
  int count=0;
  double t1, t_total;
    
  start=clock();                                         //i tipi della struct
  Hashmap* hm=map_load("../hashes.csv",MAP_SIZE,(hashFunction)hash,(hashCmp)compare_field);//hashfunction e hascmp sono due puntatori
  end=clock();
  t1=(double)(end-start)/CLOCKS_PER_SEC;//tempo in secondi
  t_total=t1;
  printf("Hashmap loaded in %f seconds\n", t1);

  start=clock();
  for(int i=0; i<KEYS_SIZE; i++) { // per ogni chiave prende il valore
    if(hashmap_get_value(hm, &(keys[i]))!=NULL)
      count++; //conta quanti elementi sono stati recuperati
  }
  end=clock();
  t1=(double)(end-start)/CLOCKS_PER_SEC;
  t_total+=t1;
  printf("Retrieved %d elements in %f seconds.\n", count, t1);
  printf("Hashmap time: %f seconds\n", t_total);

  free(hm);
}


void randomize(int* array, int lo, int hi){//prende random tutte le chiavi
  for(int i=0;i<hi;i++){
    srand(i);//per inizializzare rand e evitare che rand prenda sempre gli stessi numeri
    int num = (rand()%(hi-lo+1)+lo);//rstituisce un numero casuale da hi-1
    array[i]=num; //lo piazza nella posizione i(le chiavi)
  }
}

int main(int argc, char* argv[]){
  int* keys=malloc(sizeof(int)*KEYS_SIZE); //puntatore ad interi di dimensione keys_size
  int s=0;
 
  randomize(keys,0,KEYS_SIZE);
  printf("Please select[1.HashMap/2.Array]: ");
  scanf("%d", &s);
  if(s==1) //scelta 
    test_hashmap(keys);//scelgo l'hashmap
  else if(s==2)
    test_array(keys);
  else{
    printf("Invalid option, please reload file\n");
    exit(ERROR_EXIT_CODE);
  }

free(keys);
return 0;
}
