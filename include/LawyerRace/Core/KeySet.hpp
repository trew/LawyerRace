#ifndef LWR_KEYSET_HPP
#define LWR_KEYSET_HPP

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
