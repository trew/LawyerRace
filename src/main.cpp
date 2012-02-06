/*
*  
*
*/

#include <SDL.h>
#include <ctime>
#include "Game.h"
//#include "init_static.h"

int main(int argc, char* argv[]) {
	srand(static_cast<unsigned int>(time(NULL)));

	Game* newGame = new Game;
	return newGame->Execute();
}
