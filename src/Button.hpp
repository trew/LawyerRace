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


#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Sprite.hpp"

class Button: public Sprite {
public:
	Button();
	Button(const char* _fileName, const int _xPos, const int _yPos);
	virtual ~Button();

	void draw(SDL_Surface* _destSurf);

	void select();
	void deselect();

	bool isSelected() const;

private:
	bool selected;
};

#endif
