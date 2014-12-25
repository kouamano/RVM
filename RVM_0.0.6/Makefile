# gcc setting #
GCCWOPT = -Wall
GCCOPOPT = -O3
GCCLINKOPT = lm
# icc8 setting #
ICCWOPT = -w1
# select option #
OPT = $(ICCWOPT)
# select compiler #
CC = icc

all: rvm-init rvm-train

rvm-init: rvm-init.c rvm.c define.h files.h
	$(CC) rvm-init.c -o rvm-init $(OPT)

rvm-train: rvm-train.c rvm.c define.h files.h
	$(CC) rvm-train.c -o rvm-train $(OPT)
