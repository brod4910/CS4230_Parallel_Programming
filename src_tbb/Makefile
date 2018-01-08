.PHONY: build check help clean

help:
	@echo "Makefile for CS 4230 Parallel Programming Course, TBB Sources"
	@echo "   help      print this help documentation and exit"
	@echo "   compile   please provide SRC=<filename>"
	@echo "   run       we will create a filename.exe"

CPP=g++
OPT=-O2
CPP_OPTS=-DNDEBUG
SRC=tbb_hello_world
LINKOPTS=-ltbb -lrt

LINKPATH=$(TBB_HOME)/build/linux_intel64_gcc_cc4.8.5_libc2.17_kernel3.10.0_release/
INCLUDE_PATH=$(TBB_HOME)/include/
NUM_THREAD=8

compile:
	$(CPP) $(OPT) $(CPP_OPTS) -o $(SRC).exe $(SRC).cpp -I$(INCLUDE_PATH) -L$(LINKPATH) $(LINKOPTS)

run:
	./$(SRC).exe $(NUM_THREADS)

clean:
	rm -rf *.exe
