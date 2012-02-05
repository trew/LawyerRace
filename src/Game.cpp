#include "Game.h"

Game Game::StateControl;
SDL_Surface* Game::mainScreen;

Game::Game() 
{
}

Game::~Game()
{
}

bool Game::Init()
{
	// Initialize SDL
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) return false;

	// Set properties for the main window
	if ( (mainScreen = SDL_SetVideoMode(800, 600, 32, SDL_DOUBLEBUF | SDL_HWSURFACE)) == NULL ) return false; 

	return true; // everything ok!
}

void Game::Cleanup()
{
	SDL_FreeSurface(mainScreen);
	SDL_Quit();
}

int Game::Execute()
{
	if (!Init()) return -1;

/*	currentState->Init();
	while(currentState != NULL) 
	{
		currentState->Execute();
	}
*/

	Cleanup();
	return 0;
}

