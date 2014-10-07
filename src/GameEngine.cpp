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


#include "GameEngine.hpp"

GameEngine* GameEngine::Instance = NULL;
SDL_Window* GameEngine::window;
SDL_Surface* GameEngine::screenSurface;
lua_State* GameEngine::LuaState = NULL;

GameEngine::GameEngine()
{
	SDL_assert(!Instance);

	Instance = this;
    gameState = new GameState();
	LuaState = luaL_newstate();
	luaL_openlibs(LuaState);
	m_running = false;
}

GameEngine::~GameEngine()
{
	lua_close(LuaState);
}

bool GameEngine::Init()
{
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) return false;

	window = SDL_CreateWindow(config::WINDOW_TEXT.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		config::W_WIDTH, config::W_HEIGHT,
		SDL_WINDOW_OPENGL);
	screenSurface = SDL_GetWindowSurface(window);

	//renderer = SDL_CreateRenderer(window, -1, 0);

	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
	//SDL_RenderSetLogicalSize(sdlRenderer, 640, 480);

    TTF_Init();
	IMG_Init(IMG_INIT_PNG);

    return true;
}

void GameEngine::ChangeState(AbstractState* state) {
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameEngine::PushState(AbstractState* state)
{
	// pause current state
	if (!states.empty()) {
		//states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameEngine::PopState()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if (!states.empty()) {
		//states.back()->Resume();
	}
}
void GameEngine::Cleanup()
{
	for each (AbstractState* state in states)
	{
		state->Cleanup();
		delete state;
	}
	SDL_DestroyWindow(window);
    TTF_Quit();
	IMG_Quit();
    SDL_Quit();
}

void GameEngine::Run() {
	if (m_running) return;
	m_running = true;

	if (!Init()) return;

	GameState* gameState = new GameState();
	ChangeState(gameState);
		
	while (m_running)
	{
		SDL_Event ev;
		while (m_running) {
			AbstractState* currentState = states.back();
			while (SDL_PollEvent(&ev)) {
				currentState->HandleEvent(ev);
			}
			if (!m_running) break; // If any event handling made the game exit

			currentState->Update();
			currentState->Render();

			if (FPS::FPSControl.GetFPS() > 200) SDL_Delay(3); //Tiny delay if computer is giving high fps. No need for super high fps.
		}
	}

	Cleanup();

	return;
}

void GameEngine::Exit() {
	m_running = false;
}