a.out : main.o route-records.o
	gcc main.o route-records.o -o a.out

main.o : main.c route-records.h
	gcc -Wall -c main.c

route-records.o : route-records.c route-records.h
	gcc -Wall -c route-records.c

clean : rm *.o a.out
