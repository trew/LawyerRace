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

class Entity: public Sprite {
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
    Entity(const std::string _fileName, const int _xPos, const int _yPos);


    /**
     *  Destructor
     */
    virtual ~Entity();


    /**
     *  Drawing function
     *
     *  @param _destSurf Surface to which the entity will be drawn
     */
    virtual void draw(SDL_Surface* _destSurf, float timeAlpha);


    /**
     *  Event handling function
     *
     *  @param ev Struct containing the information about the event
     */
    virtual void handleEvent(SDL_Event& ev);


    /**
     *  Checks for collision between 2 entities
     *
     *  @param _entityA The first entity
     *  @param _entityB The second entity
     *  @return True if the entities intersect, False otherwise
     */
    static bool collides(Entity* _entityA, Entity* _entityB);

protected:
    float m_vel;
    bool moving;

public:
    static std::list<Entity*> s_entityList;
};

#endif
