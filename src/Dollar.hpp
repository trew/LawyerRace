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
