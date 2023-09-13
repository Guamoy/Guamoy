CC = gcc
CFLAGS = -g
all: $(PROGRAMS)
assign4.o: assign4.c assign4.h
	$(CC) $(CFLAGS) -c assign4.c
assign4: assign4.o
	$(CC) $(CFLAGS) -o assign4 assign4.o
clean:
	rm -f *.o
