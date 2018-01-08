.PHONY: build check help clean

help:
	@echo "Makefile for CS 4230 Parallel Programming Course, TBB Sources"
	@echo "   help      print this help documentation and exit"
	@echo "   compile   please provide SRC=<filename>"
	@echo "   run       we will create a filename.exe"

CC=gcc
CC_OPTIONS=-g -Wall
SRC=pt_hello_world
LOPTS=-lpthread
THREADS=8

compile:
	$(CC) $(CC_OPTIONS) -o $(SRC).exe $(SRC).c $(LOPTS)

run:
	./$(SRC).exe $(THREADS)

clean:
	rm -rf *.exe
