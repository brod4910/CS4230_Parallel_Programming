# Compiler
CC 			:= gcc

ifeq ($(CC), gcc)
STANDARD := -std=c99
LANG_EXT := c
endif

ifeq ($(CC), g++)
STANDARD := -std=c++11
LANG_EXT := cpp
endif

# Compiler Options
CC_OPTS	:= $(STANDARD) -g -Wa,-a,-ad

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
INC_PATH_3 := $(CS_4230_HOME)/lib/tbb/include/
INC_PATH := -I$(INC_PATH_1) -I$(INC_PATH_2) -I$(INC_PATH_3)

LIB_PATH := -L$(CS_4230_HOME)/lib/tbb/lib/

SANITIZER :=
LMATH := -lm
LPTHREAD := -lpthread

PARLIB :=

ifeq (${PARLIB}, openmp)
OPENMP := -fopenmp
endif

ifeq (${PARLIB}, tbb)
TBB := -ltbb
endif

LINK_OPTS := $(LPTHREAD) $(LMATH)

CC_OPTIM  	:= -O0

.PHONY: deploy check-env build clean help run check

all: deploy compile decompile

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
	@echo " "
	$(CC) $(CC_OPTS) $(CC_OPTIM) $(W_OPTS) \
		$(INC_PATH) $(LIB_PATH) $(OPENMP) -o $(SRC).exe $(SRC).$(LANG_EXT) \
		$(SANITIZER) $(LINK_OPTS) $(TBB) > $(SRC).lst
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

deploy: check-env

check-env:
ifndef CS_4230_INCLUDE
	$(error CS_4230_HOME UNDEFINED \
	$ source ~/CS_4230/dotcshrc)
endif

help:
	@echo "Makefile for CS_4230"
	@echo " help print this documentation and exit"
	@echo " clean"
	@echo " compile"
	@echo " decompile"
