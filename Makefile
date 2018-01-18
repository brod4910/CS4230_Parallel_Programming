# Compiler
CC 			:= gcc

# Compiler Options
CC_OPTS		:=-g -Wa,-a,-ad

# TODO Separate this into different file
# TODO Document these
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
-Wno-ignored-attributes \
-Wno-missing-field-initializers \
-Wdouble-promotion \
-Wformat=2

INC_PATH_1 := .
INC_PATH_2 := $(CS_4230_INCLUDE)
INC_PATH := -I$(INC_PATH_1) -I$(INC_PATH_2)

SANITIZER :=
LMATH := -lm
LPTHREAD := -lpthread


LINK_OPTS := $(LPTHREAD) $(LMATH)

CC_OPTIM  	:= -O0

.PHONY: build clean help run check

all: compile decompile

clean:
	@echo " "
	@echo "Cleaning..."
	@echo " "
	rm -rf *.exe *.o *.lst *.decompile *.txt .lst *.out
	@echo " "
	@echo "Done."
	@echo " "

compile:
	@echo " "
	@echo "Compiling..."
	@echo " "
	$(CC) $(CC_OPTS) $(CC_OPTIM) $(W_OPTS) \
		$(INC_PATH) -o $(SRC).exe $(SRC).c $(SANITIZER) $(LINK_OPTS)  > $(SRC).lst
	@echo " "
	@echo "Done."
	@echo " "

decompile:
	@echo " "
	@echo "De-Compiling..."
	@echo " "
	objdump -S $(SRC).exe > $(SRC).decompile
	@echo " "
	@echo "Done."
	@echo " "

help:
	@echo "Makefile for Assignment 1"
	@echo " help print this documentation and exit"
	@echo " clean"
	@echo " compile"
	@echo " decompile"
