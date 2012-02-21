#include "Game.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Log.h"
#include "GameConfig.h"

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
    LOG_DEBUG("Opening " + config::path + config::settings_file + "...");
	infile.open( (config::path + config::settings_file).c_str() );
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
					GameConfig cfg;
					if(row.find("1") == (row.find("=") +1)) {
						cfg.name = "Easy";
						cfg.max_enemies = 4;
						cfg.enemies_before_rock = 4;
						cfg.max_rocks = 10;
						cfg.p_velocity = 1.0f;
						cfg.e_velocity = 0.43f;
						cfg.r_velocity[0] = 0.9f;
						cfg.r_velocity[1] = 0.70f;
						cfg.r_velocity[2] = 0.4f;
					} else if(row.find("2") == (row.find("=") +1)) {
						cfg.name = "Medium";
						cfg.max_enemies = 5;
						cfg.enemies_before_rock = 3;
						cfg.max_rocks = 10;
						cfg.p_velocity = 1.0f;
						cfg.e_velocity = 0.53f;
						cfg.r_velocity[0] = 1.0f;
						cfg.r_velocity[1] = 0.75f;
						cfg.r_velocity[2] = 0.5f;
					} else if(row.find("3") == (row.find("=") +1)) {
						cfg.name = "Hard";
						cfg.max_enemies = 8;
						cfg.enemies_before_rock = 2;
						cfg.max_rocks = 20;
						cfg.p_velocity = 1.0f;
						cfg.e_velocity = 0.65f;
						cfg.r_velocity[0] = 1.15f;
						cfg.r_velocity[1] = 0.85f;
						cfg.r_velocity[2] = 0.7f;
					}
					if (cfg.name != "") {
						config::loadConfig(cfg);
					} // else standard values in config.cpp is used.
			}
		}
		infile.close();
	} else {
        LOG_ERROR("Couldn't load settings");
		return false;
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

