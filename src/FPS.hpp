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


/* FPS control */

#ifndef _FPS_H_
#define _FPS_H_

#include <SDL.h>
#include "Gameconfig.hpp"

class FPS {
public:

    /**
     *  Constructor
     */
    FPS();


    /**
     *  Destructor
     */
    virtual ~FPS();


    /**
     *  Update function. Must be called every frame to update correct FPS.
     */
    void Update();


    /**
     *  Retrieves the current FPS.
     *
     *  @return Current FPS
     */
    int GetFPS();


public:
    static FPS FPSControl;

private:
    unsigned int oldTime;
    unsigned int lastTime;
    unsigned int numFrames;
    unsigned int frames;
};

#endif
