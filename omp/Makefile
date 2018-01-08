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
