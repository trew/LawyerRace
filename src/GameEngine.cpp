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
#include "Log.hpp"

SDL_Window* GameEngine::window;
SDL_Surface* GameEngine::screenSurface;
lua_State* GameEngine::LuaState = NULL;

GameEngine::GameEngine()
{
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
		states.back()->Pause();
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
		states.back()->Resume();
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

	GameState* gameState = new GameState(this);
	ChangeState(gameState);
		
	float accumulator = 0;
	float timeStep = 1 / 10.f;
	SDL_Event ev;

	long lastTime = SDL_GetTicks();
	while (m_running) {
		float deltaTime = (SDL_GetTicks() - lastTime) / 1000.f;
		lastTime = SDL_GetTicks();
		accumulator += deltaTime * config::GAME_SPEED;

		AbstractState* currentState = states.back();
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT || (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE)) {
				Exit();
				break;
			}
			if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_k)
				config::ENABLE_LERP = !config::ENABLE_LERP;

			currentState->HandleEvent(ev);
		}
		if (!m_running) break; // If any event handling made the game exit

		int loops = 0;
		while (accumulator > timeStep && loops < config::MAX_FRAMESKIP) {
			currentState->Update(timeStep);
			accumulator -= timeStep;
			loops++;
		}

		float alpha = accumulator / timeStep;

		currentState->Render(alpha);

		FPS::FPSControl.Update();

//		if (FPS::FPSControl.GetFPS() > 200) SDL_Delay(3); //Tiny delay if computer is giving high fps. No need for super high fps.
	}

	Cleanup();

	return;
}

void GameEngine::Exit() {
	m_running = false;
}