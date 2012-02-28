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


#ifndef _KEYSET_H_
#define _KEYSET_H_

#include <SDL/SDL.h>
#include <string>
#include <map>

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
	/*!
	 *	Parses a file using boost::program_options.
	 */
	static bool LoadKeysetFromFile(KeySet* _ks, std::string _file); 

	SDLKey K_UP;
	SDLKey K_DOWN;
	SDLKey K_LEFT;
	SDLKey K_RIGHT;
	SDLKey K_STOP;

private:
	static bool keymap_setup;
	static void setKey(SDLKey& key, std::string _referencekey, std::string _keyname);
	static void SetupKeymap();
	static std::map<std::string, SDLKey> __keymap;
};

#endif
