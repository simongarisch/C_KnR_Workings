CC = gcc
CFLAGS = -g -w -Wall


test_add: test_add.o ../src/add.o
	$(CC) $(CFLAGS) test_add.o ../src/add.o -o test_add


clean:
	rm *.o test_add


run:
	./test_add
