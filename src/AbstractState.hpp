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


/* Abstract state in the game */

#ifndef _ABSTRACTSTATE_H_
#define _ABSTRACTSTATE_H_

#include <SDL.h>

class GameEngine;

class AbstractState {
public:

    /**
     *  Basic destructor
     */
	virtual ~AbstractState();


    /**
     *  Function to be run when the state is first initialized.
     */
    virtual bool init()=0;


	/**
	*  Function to be run before the state is destroyed.
	*/
	virtual void cleanup() = 0;
	
	virtual void pause();
	virtual void resume();

	virtual void handleEvent(SDL_Event &ev) = 0;
	virtual void copyDataForInterpolation();
	virtual void update(float timeStep) = 0;
	virtual void render(float timeAlpha) = 0;

	GameEngine* getEngine();
protected:
	AbstractState(GameEngine* engine);

private:
	GameEngine* m_engine;

};

#endif
