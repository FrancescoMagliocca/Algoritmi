#include "sorter.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <signal.h>
#include <math.h>

#define INSERTIONSORT 0
#define INTERVAL 600000
#define QUICKSORT 1
#define ERROR_EXIT_CODE 1


typedef struct {
  CmpFunc cf;
  int alg;
  int print;
  char const* filename;
} Options;

typedef struct _Record{
  int id;
  char* field1;
  int field2;
  float field3;
} Record;



static int size;
static Record** arr;
static char* time_diff;

int compare_field1(Record* r1, Record* r2){
  return strcmp(r1->field1, r2->field1);
}

int compare_field2(Record* r1, Record* r2){
  return r1->field2 - r2->field2;
}

int compare_field3(Record* r1, Record* r2){
  if(r1->field3 == r2->field3)
    return 0;
  else if(r1->field3 > r2->field3)
    return 1;
  else
    return -1;
}


void print_usage() {
  printf("ex1_app < i | q > < 1 | 2 | 3 > <filename> [p]\n");
  printf(" Selezione algoritmo: 'i'=INSERTSORT o 'q'=QUICKSORT\n");
  printf(" Seleziona il field da ordinare: 1-2 o 3\n");
  printf(" inserisci 'p' per stampare il field ordinato\n");
}



Record** load_data(char const* filename, int* size){
  FILE* file = fopen(filename, "r");
  #define MAX_BUF_LEN 1024
  char buf[MAX_BUF_LEN];
  int  id, field2;
  float field3;
  int record_n = 0, n, lines = 0;

  if(file != NULL){
    while(!feof(file)){
      fgets(buf, 1024, file);//legge le stringhe del file fino a 1024
      lines++;
    }
    lines--;
    fseek(file, 0, SEEK_SET);//riporta il puntatore al file all'inizio
    Record** arr = (Record**) malloc(sizeof(Record*) * lines);

    while(!feof(file)) {//legge ogni riga e sakva ogni elemento al suo posto
      Record* record = (Record*) malloc(sizeof(Record));//crea il record grosso quanter sono le linee del file
      int n = fscanf(file, "%d,%1024[^,],%d,%f\n", &id, buf, &field2, &field3);//controlla il numero di elenebyi del file,devono essere 4
      if(n != 4) {
        printf("Errore nella lettura del file, in linea: %d\n", record_n + 1);
        exit(ERROR_EXIT_CODE);
      }

      record->id = id;
      record->field1 = strndup(buf, MAX_BUF_LEN);
      record->field2 = field2;
      record->field3 = field3;

      arr[record_n] = record;
      record_n++;
    }
    *size = lines;
    return arr;
  } else {
    printf("Errore: il file \'%s\' non esiste\n", filename);
    exit(ERROR_EXIT_CODE);
  }
}

void free_data(){
  for(int i = 0; i < size; i++){
    free(arr[i]->field1);
    free(arr[i]);
  }
  free(arr);
}

void print_array(Record** arr, int size){
  for(int i = 0; i< size; i++){
    printf("%d,%s,%d,%f\n",arr[i]->id,arr[i]->field1,arr[i]->field2,arr[i]->field3);
  }
}



Options parse_options(int argc, char *argv[]) {// controlla che il numero di input dal terminale sia corretto
  if(argc != 4 && argc != 5) {//4 o 5 (il 5 per la p)
    printf("Errore nell'inserimento dei parametri\n");
    print_usage();//se sbagli ti stampa
    exit(ERROR_EXIT_CODE);
  }

  Options options;

  if(!strcmp(argv[1], "i")) {
    options.alg = INSERTIONSORT;
  } else if(!strcmp(argv[1], "q" )) {
    options.alg = QUICKSORT;
  } else {
    printf("Errore nell'inserimento dei parametri\n");
    print_usage();
    exit(ERROR_EXIT_CODE);
  }

  if( !strcmp(argv[2], "1") ) {
    options.cf = (CmpFunc) compare_field1;
  } else if(!strcmp(argv[2], "2" )) {
    options.cf = (CmpFunc) compare_field2;
  } else if(!strcmp(argv[2], "3" )) {
    options.cf = (CmpFunc) compare_field3;
  } else {
    printf("Errore nell'inserimento dei parametri\n");
    print_usage();
    exit(ERROR_EXIT_CODE);
  }

  options.filename = argv[3];

  if(argc == 5){
    if(!strcmp(argv[4], "p"))
      options.print = 1;
    else
    {
     printf("Errore nell'inserimento dei parametri\n");
      print_usage();
      exit(ERROR_EXIT_CODE);
    }
  } else
    options.print = 0;
  

  return options;
}

void exit_func(){
  printf("Ordinamento interrotto. Il tempo supera i 10 min\n");
  free_data();
  free(time_diff);
  exit(0);
}

void set_timer(){
  struct itimerval it_val;

  if (signal(SIGALRM, (void (*)(int)) exit_func) == SIG_ERR) {
    perror("Errore:SIGALRM");
    exit(ERROR_EXIT_CODE);
  }
  it_val.it_value.tv_sec =     INTERVAL/1000;
  it_val.it_value.tv_usec =    (INTERVAL*1000) % 1000000;	
  it_val.it_interval = it_val.it_value;
  if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
    perror("Errore:setitimer()");
    exit(ERROR_EXIT_CODE);
  }
  
}



void getTimeDifference(char* time_diff, struct timeval t_start, struct timeval t_end){
  int h, min, sec, ms;
  long t;
  t = (int)(((t_end.tv_sec - t_start.tv_sec) * 1000) + ((t_end.tv_usec - t_start.tv_usec) / 1000.0));
  ms = t % 1000;
  t = t / 1000;
  h = t / 3600;
  min = (t % 3600)/ 60;
  sec = t % 60;
  if(h == 0) {
		if(min == 0)
      sprintf(time_diff, "%d s %d ms", sec, ms);
		else
      sprintf(time_diff, "%d min %d s %d ms", min, sec, ms);
	} else
		sprintf(time_diff, "%d h %d min %d s %d ms", h, min, sec, ms);
}




int main(int argc, char *argv[]){
  struct timeval t_start,t_end;//struttura per il tempo
  time_diff = (char*) malloc(sizeof(char) * 50);//libera spazio per 50 char
  Options op = parse_options(argc, argv);//gli nput che ho scelto
  printf("\nCaricamento file \n");
  arr = load_data(op.filename, &size);
  if(!op.print)
   printf("Il file è stato caricato. Num elementi: %d\n", size);//size è uguale a lines
  gettimeofday(&t_start, NULL);

  set_timer();//setta il timer
  printf("\nOrdinamento...\n");
  if(op.alg == INSERTIONSORT)
    insertionsort((void**)arr, size, op.cf);
  else
    quicksort((void**)arr, size, op.cf);

  gettimeofday(&t_end, NULL);
  getTimeDifference(time_diff, t_start, t_end);//trova il tempo impiegato
  if(!op.print)
  printf("Tempo ordinamento: %s\n", time_diff);
  if(op.print)
    print_array(arr, size);

  
  free_data();
  free(time_diff);
}