# Makefile for Lawyer Race
# (C) 2012 Samuel Andersson
#
# Compiler: G++
#


EXECUTABLE = lwrace

SRC_DIR = src
FILES = config.cpp Button.cpp Dollar.cpp Enemy.cpp Entity.cpp FPS.cpp Game.cpp GameState.cpp GameState_Init.cpp Image.cpp main.cpp Player.cpp Rock.cpp \
        Sprite.cpp Text.cpp

SOURCES = $(foreach $(FILES), $(SRC_DIR), $(wildcard $(SRC_DIR)/*.cpp))
OBJECTS = $(FILES:.cpp=.o)

CC = g++
SDLFLAGS = -I$(shell pwd)/include/SDL/linux
CXXFLAGS = -Wall -Wextra -pedantic -g $(SDLFLAGS) -DLWPATH=\"YOYO\"

SDLLIBS = -L$(shell pwd)/libs/linux -lSDL -lpthread -lSDL_ttf -lSDL_image -lSDL_gfx
LIBS = $(SDLLIBS) -lstdc++

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LIBS) $^ -o $@

$(OBJECTS) : $(SOURCES)
	$(CC) $(CXXFLAGS) -c $^

clean :
	rm -rf *.o $(EXECUTABLE)

