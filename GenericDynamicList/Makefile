##########################################################################
# File name:  Makefile
# Author:     Damon Holland
# Date:       9.19.19
# Class:      CS 300
# Assignment: GenericDynamicList
# Purpose: 	  Makefile for List Assignment
##########################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/listdriver

bin: 
	mkdir -p bin

bin/listdriver: bin/listdriver.o bin/list.o
	${CC} ${CFLAGS} bin/listdriver.o bin/list.o -o bin/listdriver

bin/listdriver.o: src/listdriver.c include/list.h
	${CC} ${CFLAGS} -c src/listdriver.c -o bin/listdriver.o
	 
bin/list.o: src/list.c include/list.h
	${CC} ${CFLAGS} -c src/list.c -o bin/list.o
	
valgrind: bin/listdriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
 	--show-leak-kinds=all bin/listdriver
 	
tarball: clean
	tar czf ../cs300_2B_holl9358.tar.gz ../GenericDynamicList
 	
clean:
	rm -rf bin/*.o bin/listdriver