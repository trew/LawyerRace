# Makefile for Lawyer Race
# (C) 2012 Samuel Andersson
#
# Compiler: G++
#

EXECUTABLE = lwrace

SRC_DIR = src
FILES = Game.cpp main.cpp 

SOURCES = $(foreach $(FILES), $(SRC_DIR), $(wildcard $(SRC_DIR)/*.cpp))
OBJECTS = $(FILES:.cpp=.o)

CC = g++
CFLAGS = -Wall -Wextra -pedantic -g $(shell sdl-config --cflags)

LIBS = $(shell sdl-config --libs) -lstdc++

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LIBS) $^ -o $@

$(OBJECTS) : $(SOURCES)
	$(CC) $(CFLAGS) -c $^

clean :
	rm -rf *.o lwrace


