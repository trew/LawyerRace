#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Sprite.h"
#include "config.h"
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
