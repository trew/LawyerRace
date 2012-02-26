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

