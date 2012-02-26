#ifndef _ROCK_H_
#define _ROCK_H_

#include "Entity.hpp"
#include "Gameconfig.hpp"
#include "FPS.hpp"

class Rock: public Entity {
public:
	Rock();
	Rock(const std::string _fileName, const int _xPos, const int _yPos, const int _rockType);
	virtual ~Rock();

	void draw(SDL_Surface* _destSurf);
	void update();

	bool isExpired() const;
	void expire();

private:
	bool m_expired;
public:
	static std::list<Rock*> s_rockList;
};

#endif
