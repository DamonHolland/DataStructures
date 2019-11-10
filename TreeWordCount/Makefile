##########################################################################
# File name:  Makefile
# Author:     Damon Holland
# Date:       11.4.19
# Class:      CS 300
# Assignment: TreeWordCount
# Purpose: 	  Makefile for Tree Assignment
##########################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/treedriver

bin: 
	mkdir -p bin

bin/treedriver: bin/treedriver.o bin/tree.o
	${CC} ${CFLAGS} bin/treedriver.o bin/tree.o -o bin/treedriver

bin/treedriver.o: src/wordCountDriver.c include/tree.h
	${CC} ${CFLAGS} -c src/wordCountDriver.c -o bin/treedriver.o
	 
bin/tree.o: src/tree.c include/tree.h
	${CC} ${CFLAGS} -c src/tree.c -o bin/tree.o
	
valgrind: bin/treedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
 	--show-leak-kinds=all bin/treedriver
 	
tarball: clean
	tar czf ../cs300_5_holl9358.tar.gz ../TreeWordCount
 	
clean:
	rm -rf bin/*.o bin/treedriver