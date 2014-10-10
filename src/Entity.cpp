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

Entity::Entity() : m_destroyed(false) {
	manager = EntityManager::Instance;
    s_entityList.push_back(this);
}

Entity::Entity(const std::string _fileName)
	: Sprite(_fileName), m_destroyed(false)
{
	manager = EntityManager::Instance;
	s_entityList.push_back(this);
}
Entity::Entity(const std::string _fileName, const float _xPos, const float _yPos)
	: Sprite(_fileName, _xPos, _yPos), m_destroyed(false)
{
	manager = EntityManager::Instance;
	m_moving = false;
	m_xVel = 0;
	m_yVel = 0;
	m_prevX = m_xPos;
	m_prevY = m_yPos;
    s_entityList.push_back(this);
}

Entity::Entity(const std::string _fileName, const float _xPos, const float _yPos, const float _xVel, const float _yVel) 
	: Sprite(_fileName, _xPos, _yPos), m_destroyed(false)
{
	manager = EntityManager::Instance;
	m_moving = false;
	m_xVel = _xVel;
	m_yVel = _yVel;
	m_prevX = m_xPos;
	m_prevY = m_yPos;
	s_entityList.push_back(this);
}

Entity::~Entity() {
    s_entityList.remove(this);
}

void Entity::copyDataForInterpolation() {
	m_prevX = m_xPos;
	m_prevY = m_yPos;
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

void Entity::render(SDL_Surface* _destSurf, float timeAlpha) {
	if (!isVisible()) return;

	float x = lerp(m_prevX, m_xPos, timeAlpha);
	float y = lerp(m_prevY, m_yPos, timeAlpha);
	Sprite::render(_destSurf, x, y);
}

float Entity::getVelocityX() const {
	return m_xVel;
}

float Entity::getVelocityY() const {
	return m_yVel;
}

void Entity::setVelocity(const float x, const float y) {
	m_xVel = x;
	m_yVel = y;
}

float Entity::getPreviousX() const {
	return m_prevX;
}

float Entity::getPreviousY() const {
	return m_prevY;
}

void Entity::setPreviousX(const float x) {
	m_prevX = x;
}

void Entity::setPreviousY(const float y) {
	m_prevY = y;
}

bool Entity::isMoving() const {
	return m_moving;
}

void Entity::setMoving(bool moving) {
	m_moving = moving;
}

float Entity::lerp(float start, float end, float alpha) {
	if (config::ENABLE_LERP)
		return start + (end - start) * alpha;
	return end;
}
