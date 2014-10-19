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
SDL_Renderer* GameEngine::renderer;
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

bool GameEngine::init()
{
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) return false;

	window = SDL_CreateWindow(config::WINDOW_TEXT.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		config::W_WIDTH, config::W_HEIGHT,
		SDL_WINDOW_OPENGL);

	renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.

	TTF_Init();
	IMG_Init(IMG_INIT_PNG);

    return true;
}

void GameEngine::changeState(AbstractState* state) {
	// cleanup the current state
	if (!states.empty()) {
		states.back()->cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->init();
}

void GameEngine::cleanup()
{
	for (AbstractState* state : states)
	{
		state->cleanup();
		delete state;
	}
	SDL_DestroyWindow(window);
    TTF_Quit();
	IMG_Quit();
    SDL_Quit();
}

void GameEngine::run() {
	if (m_running) return;
	m_running = true;

	if (!init()) return;

	GameState* gameState = new GameState(this);
	changeState(gameState);
	
	// TODO: Move this to config?
	float timeStep = 1 / 60.f; //60 updates per second

	float accumulator = 0;
	SDL_Event ev;
	long lastTime = SDL_GetTicks();

	Uint32 TICKS_PER_FRAME = (Uint32)(1000 / (float)config::MAX_FPS);
	while (m_running) {

		float deltaTime = (SDL_GetTicks() - lastTime) / 1000.f;
		// TODO: limit deltaTime to avoid spiral of death
		
		lastTime = SDL_GetTicks();
		accumulator += deltaTime * config::GAME_SPEED;



		///// EVENT HANDLING /////
		AbstractState* currentState = states.back();
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT || (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE)) {
				exit();
				break;
			}
			if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_k)
				config::ENABLE_LERP = !config::ENABLE_LERP;

			currentState->handleEvent(ev);
		}
		if (!m_running) break; // If any event handling made the game exit
		//////////////////////////



		///// TICKING THE GAME /////
		int loops = 0;
		while (accumulator >= timeStep && loops < config::MAX_FRAMESKIP) {
			
			// there is no need to copy data for interpolation if another update is happening before the render
			if (accumulator < timeStep * 2 && loops <= config::MAX_FRAMESKIP)
				currentState->copyDataForInterpolation();

			currentState->update(timeStep);
			accumulator -= timeStep;
			loops++;
		}
		////////////////////////////



		///// RENDERING /////
		// clear the screen before rendering
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		// for rendering interpolation
		float alpha = accumulator / timeStep;

		// render all states in reverse order
		std::for_each(states.rbegin(), states.rend(), [&alpha](AbstractState* state) {
			state->render(alpha);
		});
		/////////////////////

		FPS::FPSControl.Update();

		Uint32 ticks = SDL_GetTicks() - lastTime;
		if (ticks < TICKS_PER_FRAME) {
			SDL_Delay(TICKS_PER_FRAME - ticks);
		}
	} // main loop

	cleanup();

	return;
}

void GameEngine::exit() {
	m_running = false;
}