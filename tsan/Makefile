.PHONY: build clean help compile

help:
	@echo "Makefile for CS 4230 Parallel Programming Course, TSAN Sources"
	@echo "   help      print this help documentation and exit"
	@echo "   compile   please provide SRC=<filename>"
	@echo "   run       we will create a filename.exe"

CC=gcc-7.2
CC_OPTS=
TSAN_OPTS=-fsanitize=thread
TSAN_OPTS_TEMP=-static-libtsan
SRC=simple_race
THREADS=8

clean:
	rm -rf *.exe

compile:
	$(CC) -o $(SRC).exe $(TSAN_OPTS) $(TSAN_OPTS_TEMP) $(SRC).c

run:
	./$(SRC).exe $(THREADS)

