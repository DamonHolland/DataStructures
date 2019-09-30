#########################################################################
# File name:  Makefile
# Author:     Damon Holland
# Date:       9.19.19
# Class:      CS 300
# Assignment: GenericDynamicList
# Purpose: 	  Makefile for List Assignment
#########################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/driver

bin: 
	mkdir -p bin

bin/driver: bin/driver.o bin/list.o
	${CC} ${CFLAGS} bin/driver.o bin/list.o -o bin/driver

bin/driver.o: src/driver.c include/list.h
	${CC} ${CFLAGS} -c src/driver.c -o bin/driver.o
	 
bin/list.o: src/list.c include/list.h
	${CC} ${CFLAGS} -c src/list.c -o bin/list.o
 	
tarball: clean
	tar czf ../cs300_2_holl9358.tar.gz ../GenericDynamicList
 	
clean:
	rm -rf bin/*.o bin/driver