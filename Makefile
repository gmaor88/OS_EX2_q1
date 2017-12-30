# Makefile for ex2-q1 winter 2018A

CFLAGS = -Wall
LDFLAGS = -lm # not really needed for this exercise
CC = gcc -std=c99
ECHO = echo "going to compile for target $@"
POLIGON = polygon
EX = ex2_q1
WRITER = writer
OS := $(shell uname)
ifneq (,$(findstring CYGWIN_NT,$(OS)))
	EXT = .exe
else
	EXT =
endif

PROG1 = polygon$(EXT)
PROG2 = writer$(EXT)

all: $(PROG1) $(PROG2) test

$(POLIGON).o: polygon.c polygon.h
	$(CC) $(CFLAGS) $(LDFLAGS)-c $(POLIGON).c
	$(ECHO)

$(EX).o: $(EX).c $(POLIGON).h
	$(CC) $(CFLAGS) $(LDFLAGS)-c $(EX)
	$(ECHO)

$(WRITER).o: $(WRITER).c
	$(CC) $(CFLAGS) $(LDFLAGS)-c $(WRITER).c

$(PROG2): $(WRITER).o
	@echo Linking writer. . . 
	$(CC) -o $(WRITER) $(CFLAGS) $(WRITER).o

$(PROG1): $(EX).o $(POLIGON).o 
	@echo Linking . . . 
	$(CC) -o $(POLIGON) $(CFLAGS) $(POLIGON).o $(EX).o

clean:

	rm -vf *.o *.exe *.log out.txt

test:
	@echo "Executing . . ."
	@./$(PROG1) < in.txt