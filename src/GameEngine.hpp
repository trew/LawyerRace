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


/* The game class */

#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_

#include <SDL.h>
#include <vector>

#include "GameState.hpp"
//#include "MenuState.hpp"

class AbstractState;

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

class GameEngine {
public:

    /**
     *  Constructor
     */
	GameEngine();


    /**
     *  Destructor
     */
	virtual ~GameEngine();


	/**
	 * Lua State
	 */
	static lua_State* LuaState;



    /**
     *  The one and only main screen surface
     */
    static SDL_Window* window;
	static SDL_Surface* screenSurface;

	static GameEngine* Instance;

    /**
     *  Starts up SDL and other dependencies
     *
     *  @return True if successful, False otherwise.
     */
    bool Init();


    /**
     *  Deletes instances and shut down
     */
    void Cleanup();

	void ChangeState(AbstractState* state);
	void PushState(AbstractState* state);
	void PopState();

	void Run();
	void Exit();

    AbstractState* gameState;                   ///< Pointer to the initialized GameState
//  AbstractState* menuState;                   ///< Pointer to the initialized MenuState
private:
	std::vector<AbstractState*> states;

	bool m_running;
};

#endif
