##########################################################################
# File name:  Makefile
# Author:     Damon Holland
# Date:       11.17.19
# Class:      CS 300
# Assignment: HashTable
# Purpose: 	  Makefile for HashTable Assignment
##########################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/htdriver

bin: 
	mkdir -p bin

bin/htdriver: bin/htdriver.o bin/ht.o
	${CC} ${CFLAGS} bin/htdriver.o bin/ht.o -o bin/htdriver

bin/htdriver.o: src/htdriver.c include/ht.h
	${CC} ${CFLAGS} -c src/htdriver.c -o bin/htdriver.o
	 
bin/ht.o: src/ht.c include/ht.h
	${CC} ${CFLAGS} -c src/ht.c -o bin/ht.o
 	
clean:
	rm -rf bin/*.o bin/htdriver