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


#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Sprite.hpp"
#include "Gameconfig.hpp"
#include <ctime>
#include <string>

class Entity: public Sprite {
public:
	Entity();
	Entity(const std::string _fileName);
	Entity(const std::string _fileName, const int _xPos, const int _yPos);
	virtual ~Entity();

	virtual void draw(SDL_Surface* _destSurf);

	virtual void handleEvent(SDL_Event& ev);

	static bool collides(Entity* _entityA, Entity* _entityB);
protected:
	float m_vel;
	bool moving;

public:
	static std::list<Entity*> s_entityList;
};

#endif
