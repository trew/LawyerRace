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


/* Basic image */

#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Sprite.hpp"

class Image: public Sprite {
public:

    /**
     *  Constructor
     */
    Image();


    /**
     *  Constructor
     *
     *  @param _fileName Full path to the image.
     *  @param _xPos     X-position of the image.
     *  @param _yPos     Y-position of the image.
     */
    Image(const char* _fileName, const int _xPos, const int _yPos);


    /**
     *  Destructor
     */
    virtual ~Image();


    /**
     *  Draws the image to a destination surface.
     *
     *  @param _destSurf The surface to which we draw the image.
     */
    void draw(SDL_Surface* _destSurf);
};

#endif
