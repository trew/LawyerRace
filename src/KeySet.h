#ifndef _KEYSET_H_
#define _KEYSET_H_

#include <SDL.h>

class KeySet {
public:
	KeySet() {}
	KeySet(SDLKey UP, SDLKey DOWN, SDLKey LEFT, SDLKey RIGHT, SDLKey STOP) {
		K_UP = UP;
		K_DOWN = DOWN;
		K_LEFT = LEFT;
		K_RIGHT = RIGHT;
		K_STOP = STOP;
	}
public:
	SDLKey K_UP;
	SDLKey K_DOWN;
	SDLKey K_LEFT;
	SDLKey K_RIGHT;
	SDLKey K_STOP;
};

#endif