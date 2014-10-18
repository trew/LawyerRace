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


/* Text object */

#ifndef _TEXT_H_
#define _TEXT_H_

#include <map>
#include "Sprite.hpp"
#include <SDL_ttf.h>

class Text: public Sprite {
public:

    /**
     *  Constructor that creates a text object from a number.
     *
     *  @param _number A number which we want to create a text from.
     *  @param _fontSize Font size of text.
     *  @param _xPos     X-position of the text.
     *  @param _yPos     Y-position of the text.
     *  @param r         Red   0-255 or 0x00 - 0xFF
     *  @param g         Green 0-255 or 0x00 - 0xFF
     *  @param b         Blue  0-255 or 0x00 - 0xFF
     */
    Text(SDL_Renderer* renderer, const int _number, const int _fontSize, const float _xPos, const float _yPos, int r, int g, int b);
    /**
     *  Constructor that creates a text object from a string.
     *
     *  @param _text     The string which we want to create a text from.
     *  @param _fontSize Font size of text.
     *  @param _xPos     X-position of the text.
     *  @param _yPos     Y-position of the text.
     *  @param r         Red   0-255 or 0x00 - 0xFF
     *  @param g         Green 0-255 or 0x00 - 0xFF
     *  @param b         Blue  0-255 or 0x00 - 0xFF
     */
	Text(SDL_Renderer* renderer, std::string _text, const int _fontSize, const float _xPos, const float _yPos, int r, int g, int b);


    /**
     *  Destructor
     */
    virtual ~Text();


    /**
     *  Drawing method. Draws the text to a destination surface.
     *
     *  @param _destSurf Surface which the text will be drawn to.
     */
    void render(SDL_Renderer* renderer);


    /**
     *  Replace the text with provided number.
     *
     *  @param _number Number which will be the new text.
     */
    void updateText(const int _number);


    /**
     *  Replace the text with provided string.
     *
     *  @param _newText The string that will be the new text.
     */
    void updateText(const std::string _newText);


    /**
     *  Converts a number to a string.
     *
     *  @param _number Integer to be converted.
     *  @return The integer in string format.
     */
    const std::string numberToText(int _number);


    /**
     *  Sets the color of the text.
     *
     *  @param r Red.   0-255 or 0x00-0xFF
     *  @param g Green. 0-255 or 0x00-0xFF
     *  @param b Blue.  0-255 or 0x00-0xFF
     */
    void setColor(int r, int g, int b);

private:
    SDL_Color m_color;
    int m_fontSize;
	SDL_Renderer* m_renderer;
public:
    static std::map<int, TTF_Font*> standard_font;
    static std::list<Text*> s_textList;
};

#endif 
