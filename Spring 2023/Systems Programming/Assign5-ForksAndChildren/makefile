PROGRAMS = childwords
CC = gcc
CFLAGS = -g
all: $(PROGRAMS)
childwords.o: childwords.c
	$(CC) $(CFLAGS) -c childwords.c
childwords: childwords.o
	$(CC) $(CFLAGS) -o childwords childwords.o
clean:
	rm -f *.o
