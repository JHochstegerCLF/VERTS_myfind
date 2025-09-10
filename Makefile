# Makefile for project main
# ****************************************************
# Variables to control Makefile operation
CC = g++
CFLAGS = -Wall -g
# ****************************************************
all: main
main: Main.o
	$(CC) $(CFLAGS) -o main Main.o
Main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
clean:
	rm –f main *.o
