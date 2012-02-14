#include "Game.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

Game Game::StateControl;
AbstractState* Game::currentState;
SDL_Surface* Game::mainScreen;

Game::Game() 
{
	gameState = new GameState;
	currentState = gameState;
}

Game::~Game()
{
}

void Game::setState(AbstractState* _newState) {
	currentState = _newState;
}

bool Game::Init()
{
	std::string row;
	std::ifstream infile;
	infile.open("../../settings.ini");
	if(infile) {
		while(!infile.eof()) 
		{
			std::getline(infile,row);
			if(row.size() > 0 && row.find("resolution") == 0) 
			{
					if(row.find("1024x768") == (row.find("=") +1)) {
						W_WIDTH = 1024;
						W_HEIGHT = 768;
					} else if(row.find("800x600") == (row.find("=") +1)) {
						W_WIDTH = 800;
						W_HEIGHT = 600;
					} else if(row.find("640x480") == (row.find("=") +1)) {
						W_WIDTH = 640;
						W_HEIGHT = 480;
					} 
			} else if(row.size() > 0 && row.find("difficulty") == 0) 
			{
					if(row.find("1") == (row.find("=") +1)) {
						DIFFICULTY = 1;
						MAX_ENEMIES = 4;
						ENEMIES_BEFORE_ROCK = 4;
						MAX_ROCKS = 10;
						E_VELOCITY = 0.38f;
						R_1_VELOCITY = 0.9f;
						R_2_VELOCITY = 0.70f;
						R_3_VELOCITY = 0.4f;
					} else if(row.find("2") == (row.find("=") +1)) {
						DIFFICULTY = 2;
						MAX_ENEMIES = 5;
						ENEMIES_BEFORE_ROCK = 3;
						MAX_ROCKS = 10;
						E_VELOCITY = 0.4f;
						R_1_VELOCITY = 1.0f;
						R_2_VELOCITY = 0.75f;
						R_3_VELOCITY = 0.5f;
					} else if(row.find("3") == (row.find("=") +1)) {
						DIFFICULTY = 3;
						MAX_ENEMIES = 8;
						ENEMIES_BEFORE_ROCK = 2;
						MAX_ROCKS = 20;
						E_VELOCITY = 0.45f;
						R_1_VELOCITY = 1.15f;
						R_2_VELOCITY = 0.85f;
						R_3_VELOCITY = 0.70f;
					}
			}
		}
		infile.close();
	} else {
		//NOTE: Throwing ints is very temporary.
		throw -1;
	}
	
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) return false;
	SDL_WM_SetCaption(WINDOW_TEXT, WINDOW_TEXT);

	if ( (mainScreen = SDL_SetVideoMode(W_WIDTH, W_HEIGHT, W_BPP, SDL_DOUBLEBUF | SDL_HWSURFACE)) == NULL ) return false;
	
	TTF_Init();

		
	return true;
}

void Game::Cleanup()
{
	SDL_FreeSurface(mainScreen);
	TTF_Quit();
	SDL_Quit();
}

int Game::Execute()
{
	if (!Init()) return -1;

	while(currentState != NULL) 
	{
		currentState->Execute();
	}


	Cleanup();
	return 0;
}

