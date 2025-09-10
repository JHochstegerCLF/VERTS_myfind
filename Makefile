# Makefile for project main
# ****************************************************
# Variables to control Makefile operation
CC = g++
CFLAGS = -Wall -g
# ****************************************************
all: build run
clean:
	@rm -f out/* && echo "Clean done"
build: clean
	@g++ main.cpp -o out/myfind
run:
	@./out/myfind
