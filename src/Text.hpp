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


#ifndef _TEXT_H_
#define _TEXT_H_

#include <map>
#include "Sprite.hpp"
#include <SDL/SDL_ttf.h>

class Text: public Sprite {
public:
	Text();
	Text(const int _number, const int _fontSize, const int _xPos, const int _yPos, int r, int g, int b);
	Text(std::string _text, const int _fontSize, const int _xPos, const int _yPos, int r, int g, int b);
	virtual ~Text();

	void draw(SDL_Surface* _destSurf);
	void updateText(const int _number);
	void updateText(const std::string _newText);
	void setXPos(const float _xPos);
	void setYPos(const float _yPos);

	const std::string numberToText(int _number);

	void setColor(int r, int g, int b);

private:
	SDL_Color m_color;
	int m_fontSize;
public:
	static std::map<int, TTF_Font*> standard_font;
	static std::list<Text*> s_textList;
};

#endif 
