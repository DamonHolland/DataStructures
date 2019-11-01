##########################################################################
# File name:  Makefile
# Author:     Damon Holland
# Date:       10.21.19
# Class:      CS 300
# Assignment: Airport
# Purpose: 	  Makefile for Airport Assignment
##########################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/airportdriver

bin: 
	mkdir -p bin

bin/airportdriver: bin/airportdriver.o bin/airport.o \
	../GenericDynamicQ/bin/queue.o ../GenericDynamicPriorityQ/bin/pqueue.o \
	../GenericDynamicList/bin/list.o
	${CC} ${CFLAGS} bin/airportdriver.o bin/airport.o \
	../GenericDynamicQ/bin/queue.o ../GenericDynamicPriorityQ/bin/pqueue.o \
	../GenericDynamicList/bin/list.o -o bin/airportdriver

bin/airportdriver.o: src/airportdriver.c include/airport.h \
	../GenericDynamicQ/include/queue.h \
	../GenericDynamicPriorityQ/include/pqueue.h \
	../GenericDynamicList/include/list.h 
	${CC} ${CFLAGS} -c src/airportdriver.c -o bin/airportdriver.o
	 
bin/airport.o: include/airport.h src/airport.c \
	../GenericDynamicQ/include/queue.h \
	../GenericDynamicPriorityQ/include/pqueue.h 
	 ${CC} ${CFLAGS} -c src/airport.c -o bin/airport.o
	 
../GenericDynamicQ/bin/queue.o: 
	cd ../GenericDynamicQ; make bin/queue.o
	
../GenericDynamicPriorityQ/bin/pqueue.o:
	cd ../GenericDynamicPriorityQ; make bin/pqueue.o
	
../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; make bin/list.o
	
valgrind: bin/airportdriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
  --show-leak-kinds=all bin/airportdriver data/airport.txt
  
test1: bin/airportdriver
	bin/airportdriver data/airport.txt > bin/airport_actual.txt
	diff -s data/airportexpected.txt bin/airport_actual.txt
  
test2: bin/airportdriver
	bin/airportdriver data/airport2.txt > bin/airport2_actual.txt
	diff -s data/airport2expected.txt bin/airport2_actual.txt
  
tarball: clean
	tar czf ../cs300_4_holl9358.tar.gz ../Airport ../GenericDynamicQ \
	../GenericDynamicPriorityQ ../GenericDynamicList
 	
clean:
	rm -rf bin/*.o bin/airportdriver
	cd ../GenericDynamicQ; make clean
	