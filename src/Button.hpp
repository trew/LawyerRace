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


/* Button component in the UI */


#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Sprite.hpp"

class Button: public Sprite {
public:

    /**
     *  Basic constructor
     *
     */
    Button();


    /**
     *  Constructor
     *
     * @param _fileName The full path to the image of the button
     * @param _xPos     X-position in pixels
     * @param _yPos     Y-position in pixels
     */
    Button(const char* _fileName, const float _xPos, const float _yPos);


    /**
     *  Basic destructor
     *
     */
    virtual ~Button();


    /**
     *  Drawing function
     *
     *  @param _destSurf Surface which the button will be drawn to
     */
    void render(SDL_Surface* _destSurf);


    /**
     *  Action which selects the button
     */
    void select();


    /**
     *  Action that deselects the button
     */
    void deselect();


    /**
     *  Check whether the button is selected or not.
     *
     *  @return True if the button is selected, False if not.
     */
    bool isSelected() const;

private:
    bool selected;
};

#endif
