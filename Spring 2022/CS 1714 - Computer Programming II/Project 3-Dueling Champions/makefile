project3Exe.out : main.o champion.o
	gcc main.o champion.o -o project3Exe.out

main.o : main.c champion.h
	gcc -Wall -c main.c

champion.o : champion.c champion.h
	gcc -Wall -c champion.c

clean : rm *.o a.out
