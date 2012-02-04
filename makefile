# Makefile for Lawyer Race
# (C) 2012 Samuel Andersson
#
# Compiler: G++
#

EXECUTABLE = lwrace
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
CC = gcc
CFLAGS = -c

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	cd src; $(CC) -o ../$(EXECUTABLE) $(OBJECTS)

$(OBJECTS) :
	cd src; $(CC) $(CFLAGS) $(SOURCES)

clean :
	rm -rf src/*.o lwrace

