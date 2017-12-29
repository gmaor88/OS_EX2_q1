# Makefile for ex2-q1 winter 2018A



CFLAGS = -Wall

LDFLAGS = -lm # not really needed for this exercise

CC = gcc -std=c99

ECHO = echo "going to compile for target $@"

PROGRAM = main

WRITER = writer



OS := $(shell uname)

ifneq (,$(findstring CYGWIN_NT,$(OS)))

	EXT = .exe

else

	EXT =

endif



PROG1 = ex2$(EXT)
PROG2 = $(WRITER)$(EXT)



all: $(PROG1) $(WRITER) test



$(PROG1): $(PROGRAM).o

	$(ECHO)

	$(CC) $(CFLAGS) $(LDFLAGS) $(PROGRAM).o -o $(PROG1)


$(WRITER): $(WRITER).o

	$(ECHO)

	$(CC) $(CFLAGS) $(LDFLAGS) $(WRITER).o -o $(WRITER)



$(PROGRAM).o: $(PROGRAM).c

	$(ECHO)

	$(CC) $(CFLAGS) $(LDFLAGS) -c $(PROGRAM).c -o $(PROGRAM).o

	

$(WRITER).o: $(WRITER).c

	$(ECHO)

	$(CC) $(CFLAGS) $(LDFLAGS) -c $(PROGRAM).c -o $(WRITER).o

	

clean:

	rm -vf *.o *.exe *.log out.txt



test:

	@echo going to run test...