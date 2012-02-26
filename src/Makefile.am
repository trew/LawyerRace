# Flags to CXX compiler
AM_CXXFLAGS = --pedantic -Wall
AM_LDFLAGS = 

bindir=$(abs_top_builddir)
bin_PROGRAMS = lwrace
lwrace_SOURCES = Button.cpp Dollar.cpp Enemy.cpp Entity.cpp Filesystem.cpp FPS.cpp Game.cpp Gameconfig.cpp GameState.cpp GameState_Init.cpp \
				 Image.cpp KeySet.cpp Log.cpp main.cpp Player.cpp Rock.cpp Sprite.cpp Text.cpp

lwrace_CPPFLAGS = $(BOOST_CPPFLAGS)
lwrace_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LDFLAGS)
lwrace_LIBS = $(BOOST_PROGRAM_OPTIONS_LIBS)

