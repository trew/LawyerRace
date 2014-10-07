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


#include "Entity.hpp"
#include <iostream>

std::list<Entity*> Entity::s_entityList;

Entity::Entity() {
    s_entityList.push_back(this);
}

Entity::Entity(const std::string _fileName)
: Sprite(_fileName)
{
    s_entityList.push_back(this);
}
Entity::Entity(const std::string _fileName, const int _xPos, const int _yPos)
: Sprite(_fileName, _xPos, _yPos)
{
    s_entityList.push_back(this);
}

Entity::~Entity() {
    s_entityList.remove(this);
}

void Entity::draw(SDL_Surface* _destSurf, float timeAlpha) {
    if(!m_visible) return;

    SDL_Rect destRect;
    destRect.x = static_cast<int>(m_xPos);
    destRect.y = static_cast<int>(m_yPos);
    destRect.h = m_height;
    destRect.w = m_width;

    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.h = m_height;
    srcRect.w = m_width;

    SDL_BlitSurface(m_surf, &srcRect, _destSurf, &destRect);

}

void Entity::handleEvent(SDL_Event& ev) {
}

//Static functions

bool Entity::collides(Entity* _entityA, Entity* _entityB) {
    //topA < bottomB
    //topB < bottomA
    //rightA < leftB
    //rightB < leftA

    if ((_entityA->m_xPos + _entityA->m_width < _entityB->m_xPos)) return false;
    if ((_entityB->m_xPos + _entityB->m_width < _entityA->m_xPos)) return false;
    if ((_entityA->m_yPos + _entityA->m_height < _entityB->m_yPos)) return false;
    if ((_entityB->m_yPos + _entityB->m_height < _entityA->m_yPos)) return false;

    return true;
}
