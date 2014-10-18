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


/* Rock entity */

#ifndef _ROCK_H_
#define _ROCK_H_

#include "Entity.hpp"
#include "Gameconfig.hpp"
#include "FPS.hpp"

class Rock: public Entity {
public:

    /**
     *  Constructor
     *
     *  @param _fileName Full path to the image of the rock.
     *  @param _xPos     X-position in pixels.
     *  @param _yPos     Y-position in pixels.
     *  @param _rockType Type of rock created.
     */
    Rock(const std::string _fileName, const float _xPos, const float _yPos, const int _rockType);


    /**
     *  Destructor
     */
    virtual ~Rock();

    void update(float timeStep);
};

#endif
