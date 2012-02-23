# Makefile for Lawyer Race
# (C) 2012 Samuel Andersson
#
# Compiler: G++
#


EXECUTABLE = lwrace

SRC_DIR = src
FILES = KeySet.cpp Filesystem.cpp Log.cpp config.cpp Button.cpp Dollar.cpp Enemy.cpp Entity.cpp FPS.cpp Game.cpp \
        GameState.cpp GameState_Init.cpp Image.cpp main.cpp Player.cpp Rock.cpp Sprite.cpp Text.cpp

SOURCES = $(foreach $(FILES), $(SRC_DIR), $(wildcard $(SRC_DIR)/*.cpp))
OBJECTS = $(FILES:.cpp=.o)

CC = g++
SDLFLAGS = $(shell sdl-config --cflags)
CXXFLAGS = -Wall -Wextra -pedantic -g $(SDLFLAGS)

SDLLIBS = $(shell sdl-config --libs) -lSDL_ttf -lSDL_image
LIBS = $(SDLLIBS) -lboost_program_options   # -lstdc++

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LIBS) $^ -o $@

$(OBJECTS) : $(SOURCES)
	$(CC) $(CXXFLAGS) -c $^

clean :
	rm -rf *.o $(EXECUTABLE)

