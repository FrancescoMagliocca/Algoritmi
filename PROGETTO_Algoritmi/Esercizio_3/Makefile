CFLAGS=-g -O0 -I include -I Resources/C/Unity/

all: createdir test app
test: createdir bin/test3
app: createdir bin/app3

createdir: 
	mkdir -p bin 
	mkdir -p build

clean:
	$(RM) -rf bin/* 
	$(RM) -rf build/*

build/lib3.o: src/lib3.c include/lib3.h
	$(CC) $(CFLAGS) -c src/lib3.c -o build/lib3.o

bin/test3: test/test3.c build/lib3.o 
	$(CC) $(CFLAGS) test/test3.c build/lib3.o Resources/C/Unity/unity.c -o bin/test3

bin/app3: app/app3.c build/lib3.o 
	$(CC) $(CFLAGS) app/app3.c build/lib3.o -o bin/app3
