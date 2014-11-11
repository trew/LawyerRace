#include "LawyerRace/Core/GameEngine.hpp"
#include "LawyerRace/Utils/Log.hpp"
#include <SDL_image.h>
#include <sstream>

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

	m_window = SDL_CreateWindow(config::WINDOW_TEXT.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		config::W_WIDTH, config::W_HEIGHT,
		SDL_WINDOW_OPENGL);

	if (m_window == NULL) return false;

	if ((m_renderer = SDL_CreateRenderer(m_window, -1, 0)) == NULL) return false;
	Text::textRenderer = m_renderer;

	// make the scaled rendering look smoother.
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  

	if (TTF_Init() == -1) return false;
	if (IMG_Init(IMG_INIT_PNG) == 0) return false;

    return true;
}

void GameEngine::changeState(AbstractState* state) {
	state->m_engine = this;

	// try initializing the new state
	if (!state->init()) {
		LOG_ERROR << "State couldn't be initialized." << std::endl;
		state->cleanup();
		if (states.empty()) {
			exit();
		}
		return;
	}

	// cleanup the current state
	if (!states.empty()) {
		states.back()->cleanup();
		states.back()->m_engine = NULL;
		states.pop_back();
	}
	states.push_back(state);
}

void GameEngine::cleanup()
{
	for (AbstractState* state : states)
	{
		state->cleanup();
		delete state;
	}
	SDL_DestroyRenderer(m_renderer);
    TTF_Quit();
	IMG_Quit();
	
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool GameEngine::handleEvent(SDL_Event& ev) {
	if (ev.type == SDL_QUIT) {
		exit();
		return true;
	}
	else if (ev.type == SDL_KEYDOWN) {
		if (ev.key.keysym.sym == SDLK_ESCAPE) {
			exit();
			return true;
		} else if (ev.key.keysym.sym == SDLK_k) {
			config::ENABLE_LERP = !config::ENABLE_LERP;
			LOG_DEBUG << "Interpolation is now " << (config::ENABLE_LERP ? "enabled." : "disabled.") << std::endl;
			return true;
		}
	}
	return false;
}

int GameEngine::run() {
	if (m_running) return -1;
	m_running = true;

	if (!init()) return -1;

	GameState* gameState = new GameState();
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
			if (!handleEvent(ev))
				currentState->handleEvent(ev);
		}
		if (!m_running) break; // If any event handling made the game exit
		//////////////////////////



		///// TICKING THE GAME /////
		if (accumulator >= timeStep) {
#ifdef WIN32
			std::stringstream ss;
			ss << config::WINDOW_TEXT << "    " << fps.GetFPS();
			SDL_SetWindowTitle(m_window, ss.str().c_str());
#endif
		}

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
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
		SDL_RenderClear(m_renderer);

		// for rendering interpolation
		float alpha = accumulator / timeStep;

		// render all states in reverse order
		std::for_each(states.rbegin(), states.rend(), [&alpha](AbstractState* state) {
			state->render(alpha);
		});

		SDL_RenderPresent(m_renderer);
		/////////////////////

		fps.Update();


		// Cap frame rate if MAX_FPS is set
		if (config::MAX_FPS > 0) {
			Uint32 ticks = SDL_GetTicks() - lastTime;
			if (ticks < TICKS_PER_FRAME) {
				SDL_Delay(TICKS_PER_FRAME - ticks);
			}
		}
	} // main loop

	cleanup();

	return 0;
}

void GameEngine::exit() {
	m_running = false;
}