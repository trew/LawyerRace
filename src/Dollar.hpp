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


/* Dollar object */

#ifndef _DOLLAR_H_
#define _DOLLAR_H_

#include "Entity.hpp"

class Dollar: public Entity {
public:

    /**
     *  Basic constructor
     */
    Dollar();


    /**
     *  Constructor
     *
     *  @param _fileName Full path to image of dollar
     */
    Dollar(const std::string _fileName);


    /**
     *  Constructor
     *
     *  @param _fileName Full path to image of dollar
     *  @param _xPos     X-position for dollar in pixels
     *  @param _yPos     Y-position for dollar in pixels
     */
    Dollar(const std::string _fileName, int _xPos, int _yPos);


    /**
     *  Destructor
     */
    virtual ~Dollar();


    /**
     *  Drawing function
     *
     *  @param _destSurf Surface to which the dollar is drawn
     */
    void draw(SDL_Surface* _destSurf);


    /**
     *  Event handling function
     *
     *  @param ev Struct containing information about the polled event.
     */
    void handleEvent(SDL_Event& ev);


    /**
     *  Sets X position
     *
     *  @param _xPos X-position
     */
    void setXPos(const float _xPos);


    /**
     *  Sets Y position
     *
     *  @param _yPos Y-position
     */
    void setYPos(const float _yPos);

    static std::list<Dollar*> s_dollarList;

private:
    Uint32 startTime;
    int durationTime;
    bool expired;
};

#endif
