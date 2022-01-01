CheckCheck: main.o tripler.o
	gcc main.o tripler.o -lcheck -lm -lpthread -lrt -g -o CheckCheck


main.o: main.c
	gcc -c main.c


tripler.o:
	gcc -c tripler.c


run:
	.\CheckCheck.exe


clean:
	rm *.o
