#Makefile for ga-c

CC = gcc
CFLAGS = -c -O3 -fexpensive-optimizations 

OBJECTS = main.o runga.o ga.o fitness.o files.o random_number_generation.o misc.o params.o 

HEADER_FILES = definitions.h prototypes.h globals.h params.h 

TARGET = robby

$(TARGET) : $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) -lm 


main.o: main.c $(HEADER_FILES)
	$(CC) $(CFLAGS) main.c

runga.o: runga.c $(HEADER_FILES)
	$(CC) $(CFLAGS) runga.c

ga.o: ga.c $(HEADER_FILES)
	$(CC) $(CFLAGS) ga.c

fitness.o: fitness.c $(HEADER_FILES)
	$(CC) $(CFLAGS) fitness.c

files.o: files.c $(HEADER_FILES)
	$(CC) $(CFLAGS) files.c

random_number_generation.o: random_number_generation.c $(HEADER_FILES)
	$(CC) $(CFLAGS) random_number_generation.c

params.o: params.c $(HEADER_FILES)
	$(CC) $(CFLAGS) params.c

misc.o: misc.c $(HEADER_FILES)
	$(CC) $(CFLAGS) misc.c

clean: 
	rm -f robby *.o core



