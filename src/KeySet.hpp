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


/* A keyset class */

#ifndef _KEYSET_H_
#define _KEYSET_H_

#include <SDL.h>
#include <string>
#include <map>

namespace luabridge {
	class LuaRef;
}

class KeySet {
public:
    KeySet() {}
	KeySet(SDL_Keycode UP, SDL_Keycode DOWN, SDL_Keycode LEFT, SDL_Keycode RIGHT, SDL_Keycode STOP) {
        K_UP = UP;
        K_DOWN = DOWN;
        K_LEFT = LEFT;
        K_RIGHT = RIGHT;
        K_STOP = STOP;
    }
public:
    static bool LoadKeysetFromFile(KeySet* _ks, std::string _file); 

	SDL_Keycode K_UP;
	SDL_Keycode K_DOWN;
	SDL_Keycode K_LEFT;
	SDL_Keycode K_RIGHT;
	SDL_Keycode K_STOP;

private:
	static void setKeysForPlayer(int playerNumber, KeySet* _ks, luabridge::LuaRef table);
    static bool keymap_setup;
	static void setKey(SDL_Keycode& key, std::string _referencekey, std::string _keyname);
    static void SetupKeymap();
	static std::map<std::string, SDL_Keycode> __keymap;
};

#endif
