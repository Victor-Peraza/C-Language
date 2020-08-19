#Victor Peraza 
CC = gcc

range: lab5.o get_range_count.o 
	gcc lab5.o get_range_count.o -o range -lm

lab5.o: lab5.c lab5.h 
	gcc -c lab5.c
	
get_range_count.o: get_range_count.c lab5.h
	gcc -c get_range_count.c
