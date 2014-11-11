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

	static lua_State* LuaState;

    static SDL_Window* window;
	static SDL_Renderer* renderer;

	bool init();
	void cleanup();

	void handleEvent(SDL_Event&);

	void changeState(AbstractState* state);
	void pushState(AbstractState* state);
	void popState();

	void run();
	void exit();

private:
	std::vector<AbstractState*> states;

	FPS fps;
	bool m_running;
};

#endif
