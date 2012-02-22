#ifndef _KEYSET_H_
#define _KEYSET_H_

#include <SDL.h>
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