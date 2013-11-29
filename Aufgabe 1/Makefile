#
# Makefile for SLPL interpreter
#

CC = gcc -m32
CFLAGS = -Wall -g
LDFLAGS = -g
LDLIBS = -lm

SRCS = njvm.c
OBJS = $(patsubst %.c,%.o,$(SRCS))
BIN = slpl

.PHONY:		all run depend clean dist-clean

run:		$(BIN)
		./$(BIN)

$(BIN):		$(OBJS)
		$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o:		%.c
		$(CC) $(CFLAGS) -o $@ -c $<

