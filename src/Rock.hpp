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
     */
    Rock();


    /**
     *  Constructor
     *
     *  @param _fileName Full path to the image of the rock.
     *  @param _xPos     X-position in pixels.
     *  @param _yPos     Y-position in pixels.
     *  @param _rockType Type of rock created.
     */
    Rock(const std::string _fileName, const int _xPos, const int _yPos, const int _rockType);


    /**
     *  Destructor
     */
    virtual ~Rock();


    /**
     *  Drawing method.
     *
     *  @param _destSurf Surface which the rock will be drawn to.
     */
    void draw(SDL_Surface* _destSurf, float timeAlpha);


    /**
     *  Update. Called every frame to update the status of the rock.
     */
    void update(float timeStep);


    /**
     *  Checks if this rock has expired.
     *
     *  @return True if the rock is expired, False otherwise.
     */
    bool isExpired() const;


    /**
     *  Sets the rock to be expired. This is triggered when the rock has fallen out of screen.
     */
    void expire();

private:
    bool m_expired;
public:
    static std::list<Rock*> s_rockList;
};

#endif
