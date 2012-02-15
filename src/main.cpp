/*
*  
*
*/

#include <SDL.h>
#include <ctime>
#include "Game.h"
#include <iostream>


int main(int argc, char* argv[]) {
	srand(static_cast<unsigned int>(time(NULL)));

	Game newGame;
    try 
    {
        newGame.Execute();
    } 
	catch (int i) //TODO: Exceptions
    {
        std::cerr << "Something went terribly wrong." << std::endl;
    }
	catch (char* c)
	{
		std::cerr << c << std::endl;
	}
	return 0;
}

