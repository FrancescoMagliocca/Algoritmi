CFLAGS=-g -O0 -I include -I Resources/C/Unity/

all: bin/quicksort_test bin/insertionsort_test bin/ex1_app

clean:
	$(RM) -rf bin/*
	$(RM) -rf build/*

build/sorter.o: src/sorter.c include/sorter.h
	$(CC) $(CFLAGS) -c src/sorter.c -o build/sorter.o


bin/quicksort_test: test/quicksort_test.c build/sorter.o include/sorter.h
	$(CC) $(CFLAGS)  test/quicksort_test.c build/sorter.o Resources/C/Unity/unity.c -o bin/quicksort_test


bin/insertionsort_test: test/insertionsort_test.c build/sorter.o include/sorter.h
	$(CC) $(CFLAGS)  test/insertionsort_test.c build/sorter.o Resources/C/Unity/unity.c -o bin/insertionsort_test
	
bin/ex1_app: app/ex1_app.c build/sorter.o include/sorter.h
	$(CC) $(CFLAGS)  app/ex1_app.c build/sorter.o -o bin/ex1_app -lm
