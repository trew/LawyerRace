#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Sprite.h"

class Button: public Sprite {
public:
	Button();
	Button(const char* _fileName, const int _xPos, const int _yPos);
	virtual ~Button();

	void draw(SDL_Surface* _destSurf);

	void select();
	void deselect();

	bool isSelected() const;

private:
	bool selected;
};

#endif