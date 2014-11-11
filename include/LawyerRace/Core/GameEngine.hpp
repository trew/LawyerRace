#ifndef LWR_GAMEENGINE_HPP
#define LWR_GAMEENGINE_HPP

#include <SDL.h>
#include <vector>

#include "LawyerRace/Core/GameState.hpp"
#include "LawyerRace/Utils/FPS.hpp"

class AbstractState;

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

class GameEngine {
public:
	GameEngine();
	virtual ~GameEngine();

	static lua_State* LuaState; // TODO: change to non-static

	SDL_Window* const getWindow() { return m_window; }
	SDL_Renderer* const getRenderer() { return m_renderer; }

	int getWindowWidth() const { int w; SDL_GetWindowSize(m_window, &w, NULL); return w; }
	int getWindowHeight() const { int h; SDL_GetWindowSize(m_window, NULL, &h); return h; }

	bool init();
	void cleanup();

	bool handleEvent(SDL_Event&);

	void changeState(AbstractState* state);

	int run();
	void exit();

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	std::vector<AbstractState*> states;

	FPS fps;
	bool m_running;
};

#endif
