#include "Entity.h"
#include <iostream>

std::list<Entity*> Entity::s_entityList;

Entity::Entity() {
	s_entityList.push_back(this);
}

Entity::Entity(const char* _fileName)
: Sprite(_fileName)
{
	s_entityList.push_back(this);
}
Entity::Entity(const char* _fileName, const int _xPos, const int _yPos)
: Sprite(_fileName, _xPos, _yPos)
{
	s_entityList.push_back(this);
}

Entity::~Entity() {
	s_entityList.remove(this);
}

void Entity::draw(SDL_Surface* _destSurf) {
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
///True if entities rects intersects.

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