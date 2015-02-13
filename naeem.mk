# -------- makefile --------------

CC = g++

# Flags to the compiler

CFLAGS = -Wall

all: prime

prime: naeem.cpp
	$(CC) $(CFLAGS) naeem.cpp 

clean:
	rm -rf a.o
