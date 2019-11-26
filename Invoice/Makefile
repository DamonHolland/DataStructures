##########################################################################
# File name:  Makefile
# Author:     Damon Holland
# Date:       11.25.19
# Class:      CS 300
# Assignment: HashTable
# Purpose: 	  Makefile for Invoice
##########################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/invoice

bin: 
	mkdir -p bin

bin/invoice: bin/invoice.o ../HashTable/bin/ht.o \
	../GenericDynamicList/bin/list.o
	${CC} ${CFLAGS} bin/invoice.o ../HashTable/bin/ht.o \
	../GenericDynamicList/bin/list.o  -o bin/invoice
	
bin/invoice.o: src/invoice.c ../HashTable/include/ht.h \
	../GenericDynamicList/include/list.h 
	${CC} ${CFLAGS} -c src/invoice.c -o bin/invoice.o

../HashTable/bin/ht.o: 
	cd ../HashTable; make bin/ht.o
	
../GenericDynamicList/bin/list.o:
	cd ../GenericDynamicList; make bin/list.o
 	
valgrind: bin/invoice
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
 	--show-leak-kinds=all bin/invoice
 	
clean:
	rm -rf bin/*.o bin/invoice
	cd ../HashTable; make clean
	cd ../GenericDynamicList; make clean