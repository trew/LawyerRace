/*
*  
*
*/

#include <SDL.h>
#include <ctime>
#include "Game.h"
#include <iostream>

//#include "init_static.h"

int main(int argc, char* argv[]) {
	srand(static_cast<unsigned int>(time(NULL)));

	Game newGame;
    try 
    {
        newGame.Execute();
    } 
    catch 
    {
        std::cerr << "Something went terribly wrong." << std::endl;
    }
	return 0;
}

