# Makefile for Lawyer Race
# (C) 2012 Samuel Andersson
#
# Compiler: G++
#

EXECUTABLE = lwrace
SRC_DIR = src
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
CC = gcc
CFLAGS = -c

all : lwrace

lwrace : $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS)

$(OBJECTS) :
	$(CC) $(CFLAGS) $(SRC_DIR)/$(SOURCES)

clean :
	rm -rf $(SRC_DIR)/*.o lwrace

