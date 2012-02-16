#include "Game.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Log.h"

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
    LOG_DEBUG("Opening " + config::path + "/settings.ini...");
	infile.open( (config::path + "/settings.ini").c_str() );
	if(infile) {
		while(!infile.eof()) 
		{
			std::getline(infile,row);
			if(row.size() > 0 && row.find("resolution") == 0) 
			{
					if(row.find("1024x768") == (row.find("=") +1)) {
					config::W_WIDTH = 1024;
					config::W_HEIGHT = 768;
					} else if(row.find("800x600") == (row.find("=") +1)) {
					config::W_WIDTH = 800;
					config::W_HEIGHT = 600;
					} else if(row.find("640x480") == (row.find("=") +1)) {
					config::W_WIDTH = 640;
					config::W_HEIGHT = 480;
					} 
			} else if(row.size() > 0 && row.find("difficulty") == 0) 
			{
					if(row.find("1") == (row.find("=") +1)) {
					config::DIFFICULTY = 1;
					config::MAX_ENEMIES = 4;
					config::ENEMIES_BEFORE_ROCK = 4;
					config::MAX_ROCKS = 10;
					config::E_VELOCITY = 0.4f;
					config::R_1_VELOCITY = 0.9f;
					config::R_2_VELOCITY = 0.70f;
					config::R_3_VELOCITY = 0.4f;
					} else if(row.find("2") == (row.find("=") +1)) {
					config::DIFFICULTY = 2;
					config::MAX_ENEMIES = 5;
					config::ENEMIES_BEFORE_ROCK = 3;
					config::MAX_ROCKS = 10;
					config::E_VELOCITY = 0.5f;
					config::R_1_VELOCITY = 1.0f;
					config::R_2_VELOCITY = 0.75f;
					config::R_3_VELOCITY = 0.5f;
					} else if(row.find("3") == (row.find("=") +1)) {
					config::DIFFICULTY = 3;
					config::MAX_ENEMIES = 8;
					config::ENEMIES_BEFORE_ROCK = 2;
					config::MAX_ROCKS = 20;
					config::E_VELOCITY = 0.6f;
					config::R_1_VELOCITY = 1.15f;
					config::R_2_VELOCITY = 0.85f;
					config::R_3_VELOCITY = 0.70f;
					}
			}
		}
		infile.close();
	} else {
		//Throwing regular strings is very temporary
        LOG_DEBUG("Couldn't load settings");
		throw "Couldn't load settings";
	}
	
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) return false;

	SDL_WM_SetCaption(config::WINDOW_TEXT.c_str(), config::WINDOW_TEXT.c_str());

	if ( (mainScreen = SDL_SetVideoMode(config::W_WIDTH, config::W_HEIGHT, config::W_BPP, SDL_DOUBLEBUF | SDL_HWSURFACE)) == NULL ) return false;
	
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

