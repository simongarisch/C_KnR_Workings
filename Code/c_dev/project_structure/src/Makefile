CC = gcc
CFLAGS = -g -w -Wall
# https://developers.redhat.com/blog/2018/03/21/compiler-and-linker-flags-gcc


main: main.o add.o
	$(CC) $(CFLAGS) main.o add.o -o main


add.o: add.h add.c
	$(CC) $(CFLAGS) -c add.c


clean:
	rm *.o main


run:
	./main
