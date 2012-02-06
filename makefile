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
SDLFLAGS = -I$(shell pwd)/include/SDL/linux
CXXFLAGS = -Wall -Wextra -pedantic -g $(SDLFLAGS)

SDLLIBS = -L$(shell pwd)/libs/linux -lSDL -lpthread
LIBS = $(SDLLIBS) -lstdc++

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LIBS) $^ -o $@

$(OBJECTS) : $(SOURCES)
	$(CC) $(CXXFLAGS) -c $^

clean :
	rm -rf *.o $(EXECUTABLE)

