/*
*  
*
*/

#include <SDL.h>
#include <ctime>
#include "Game.h"
#include <iostream>
#include "config.h"
#include "Log.h"

int main(int argc, char* argv[]) {
	srand(static_cast<unsigned int>(time(NULL)));

	Game newGame;
    try 
    {
        newGame.Execute();
    } 
	catch (const char* c)
	{
		std::cerr << "Error: " << c << std::endl;
	}
	return 0;
}

