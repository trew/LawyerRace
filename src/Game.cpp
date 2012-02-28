/*
    Lawyer Race - A game about escaping the law
    Copyright (C) 2012 Samuel Andersson

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "Game.hpp"

Game Game::StateControl;
AbstractState* Game::currentState;
SDL_Surface* Game::mainScreen;

Game::Game()
{
    gameState = new GameState();
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

