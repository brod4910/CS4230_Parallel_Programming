CC 			:= gcc
CC_OPTS		:=-g -Wa,-a,-ad 
W_OPTS		:= -Wno-variadic-macros \
	-W \
	-Wpedantic \
	-Wextra \
	-Wall \
	-Wcast-align \
	-Wcast-qual \
	-Wstrict-aliasing=2 \
	-Wframe-larger-than=32768 \
	-Wno-strict-overflow \
	-Wsync-nand \
	-Wtrampolines \
	-Wsign-compare \
	-Werror=float-equal \
	-Werror=missing-braces \
	-Werror=init-self \
	-Werror=logical-op \
	-Werror=write-strings \
	-Werror=address \
	-Werror=array-bounds \
	-Werror=char-subscripts \
	-Werror=enum-compare \
	-Werror=implicit-int \
	-Werror=empty-body \
	-Werror=main \
	-Werror=aggressive-loop-optimizations \
	-Werror=nonnull \
	-Werror=parentheses \
	-Werror=pointer-sign \
	-Werror=return-type \
	-Werror=sequence-point \
	-Werror=uninitialized \
	-Werror=volatile-register-var \
	-Werror=ignored-qualifiers \
	-Werror=missing-parameter-type \
	-Werror=old-style-declaration \
	-Wno-error=maybe-uninitialized \
	-Wno-unused-function \
	-Wodr \
	-Wformat-signedness \
	-Wsuggest-final-types \
	-Wsuggest-final-methods \
	-Wno-ignored-attributes \
	-Wno-missing-field-initializers \
	-Wdouble-promotion \
	-Wformat=2 
INC_PATH 	:= .
CFLAGS  	:= -O0

.PHONY: build clean help run check

clean:
	rm -rf *.exe *.o *.lst *.decompile *.txt 

all: compile decompile

compile:
	@echo "Compiling..."
	@$(CC) $(CC_OPTS) $(W_OPTS) -I$(INC_PATH) -o $(SRC).exe $(SRC).c > $(SRC).lst

decompile:
	@echo "De-Compiling..."
	@objdump -S $(SRC).exe > $(SRC).decompile

help:
	@echo "Makefile for q1"
	@echo " help print this documentation and exit"
