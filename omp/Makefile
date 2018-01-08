.PHONY: build check help clean

help:
	@echo "Makefile for CS 4230 Parallel Programming Course, Open MP Sources"
	@echo "   help      print this help documentation and exit"
	@echo "   compile   please provide SRC=<filename>"
	@echo "   run       we will create a filename.exe"


CC=gcc
CCOPTS=-g -Wall 
OMP_OPTS=-fopenmp
SRC=omp_hello_world
THREADS=8

compile:
	$(CC) $(CCOPTS) $(OMP_OPTS) -o $(SRC).exe $(SRC).c

run:
	./$(SRC).exe $(THREADS)

clean:
	rm -rf *.exe
