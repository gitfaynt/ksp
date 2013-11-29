#
# Makefile for SLPL interpreter
#

CC = gcc -m32
CFLAGS = -Wall -g
LDFLAGS = -g -pedantic
LDLIBS = -lm

SRCS = njvm.c
OBJS = $(patsubst %.c,%.o,$(SRCS))
BIN = njvm

.PHONY:		all run depend clean dist-clean



$(BIN):		$(OBJS)
		$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o:		%.c
		$(CC) $(CFLAGS) -o $@ -c $<
