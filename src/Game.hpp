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

#ifndef _GAME_H_
#define _GAME_H_

#include <SDL/SDL.h>
#include "GameState.hpp"
//#include "MenuState.hpp"

class Game {
public:

    /**
     *  Constructor
     */
    Game();


    /**
     *  Destructor
     */
    virtual ~Game();


    /**
     *  Singleton instance for state management
     */
    static Game StateControl;


    /**
     *  The one and only main screen surface
     */
    static SDL_Surface* mainScreen;


    /**
     *  The main execution function. This basicly starts the game.
     *
     *  @return Error code. 0 if nothing went wrong.
     */
    virtual int Execute();


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


    /**
     *  To be used with StateControl. Sets next state.
     *
     *  @param _newState Pointer to the next state
     */
    void setState(AbstractState* _newState);


    AbstractState* gameState;                   ///< Pointer to the initialized GameState
//  AbstractState* menuState;                   ///< Pointer to the initialized MenuState
private:
    static AbstractState* nextState;            ///< Holds next state (we want to be able to change the state at any point, but a state must run it's full loop until it can switch)
    static AbstractState* currentState;     ///< Holds the current state

};

#endif
