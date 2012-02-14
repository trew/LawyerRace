#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Sprite.h"

class Image: public Sprite {
public:
	Image();
	Image(const char* _fileName, const int _xPos, const int _yPos);
	virtual ~Image();

	void draw(SDL_Surface* _destSurf);

};

#endif