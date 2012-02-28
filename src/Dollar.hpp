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


#ifndef _DOLLAR_H_
#define _DOLLAR_H_

#include "Entity.hpp"

class Dollar: public Entity {
public:
	Dollar();
	Dollar(const std::string _fileName);
	Dollar(const std::string _fileName, int _xPos, int _yPos);
	virtual ~Dollar();

	void draw(SDL_Surface* _destSurf);
	void handleEvent(SDL_Event& ev);

	void setXPos(const float _xPos);
	void setYPos(const float _yPos);

public:
	static std::list<Dollar*> s_dollarList;

private:
	Uint32 startTime;
	int durationTime;
	bool expired;
};

#endif
