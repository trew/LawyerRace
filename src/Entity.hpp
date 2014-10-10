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


/* Base entity class */

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Sprite.hpp"
#include "Gameconfig.hpp"
#include <ctime>
#include <string>
#include "EntityManager.h"

class Entity: public Sprite {
friend class EntityManager;

public:

    /**
     *  Constructor
     */
    Entity();


    /**
     *  Constructor
     *
     *  @param _fileName Full path to the image of the entity
     */
    Entity(const std::string _fileName);


    /**
     *  Constructor
     *
     *  @param _fileName Full path to the image of the entity
     *  @param _xPos     X-position of the entity in pixels
     *  @param _yPos     Y-position of the entity in pixels
     */
    Entity(const std::string _fileName, const float _xPos, const float _yPos);

	Entity(const std::string _fileName, const float _xPos, const float _yPos, const float _xVel, const float _yVel);

    /**
     *  Destructor
     */
    virtual ~Entity();

	void copyDataForInterpolation();

    /**
     *  Checks for collision between 2 entities
     *
     *  @param _entityA The first entity
     *  @param _entityB The second entity
     *  @return True if the entities intersect, False otherwise
     */
    static bool collides(Entity* _entityA, Entity* _entityB);

	virtual void render(SDL_Surface* dest, float timeAlpha);

	float getVelocityX() const;
	float getVelocityY() const;
	void setVelocity(const float x, const float y);

	float getPreviousX() const;
	float getPreviousY() const;

	void setPreviousX(const float x);
	void setPreviousY(const float y);

	bool isMoving() const;
	void setMoving(bool moving);

	float lerp(float start, float end, float alpha);

	static std::list<Entity*> s_entityList;

protected:
	EntityManager* manager;

private:
	float m_xVel;
	float m_yVel;
	float m_prevX;
	float m_prevY;
	bool m_moving;

	bool m_destroyed;

};

#endif
