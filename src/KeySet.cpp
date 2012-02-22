#include "KeySet.h"
#include "config.h"
#include <boost/program_options.hpp>
#include <fstream>
#include "Log.h"

std::map<std::string, SDLKey> KeySet::__keymap;
bool KeySet::keymap_setup = false;

namespace po = boost::program_options;

void KeySet::SetupKeymap()
{
	LOG_DEBUG("Setting up keymap...");
	__keymap["up"] = SDLK_UP;
	__keymap["down"] = SDLK_DOWN;
	__keymap["left"] = SDLK_LEFT;
	__keymap["right"] = SDLK_RIGHT;
	__keymap["num_1"] = SDLK_KP1;
	__keymap["num_2"] = SDLK_KP2;
	__keymap["num_3"] = SDLK_KP3;
	__keymap["num_4"] = SDLK_KP4;
	__keymap["num_5"] = SDLK_KP5;
	__keymap["num_6"] = SDLK_KP6;
	__keymap["num_7"] = SDLK_KP7;
	__keymap["num_8"] = SDLK_KP8;
	__keymap["num_9"] = SDLK_KP9;
	__keymap["num_0"] = SDLK_KP0;
	__keymap["rctrl"] = SDLK_RCTRL;
	__keymap["lctrl"] = SDLK_LCTRL;
	__keymap["rshift"] = SDLK_RSHIFT;
	__keymap["lshift"] = SDLK_LSHIFT;
	__keymap["lalt"] = SDLK_LALT;
	__keymap["altgr"] = SDLK_MODE;
	__keymap["tab"] = SDLK_TAB;
	__keymap["insert"] = SDLK_INSERT;
	__keymap["delete"] = SDLK_DELETE;
	__keymap["home"] = SDLK_HOME;
	__keymap["end"] = SDLK_END;
	__keymap["pgup"] = SDLK_PAGEUP;
	__keymap["pgdown"] = SDLK_PAGEDOWN;
	__keymap["backspace"] = SDLK_BACKSPACE;
	__keymap["return"] = SDLK_RETURN;
	__keymap["space"] = SDLK_SPACE;
	keymap_setup = true;
}

inline bool inrange(int x,int a,int b) { return (a <= x && x <= b); } //true if a <= x <= b
inline bool in(int x, int list[]) {  //true if x exist in list
	for (int i = 0; i < sizeof(list); i++)	if (x == list[i]) return true;
	return false;
}

void KeySet::setKey(SDLKey& key, std::string _referencekey, std::string _keyname) 
{
	/* Sets key to selected key in keymap
	 * Defaults to SDLK_UNKNOWN if no key found in keymap or in Ascii table
	 * Referencekey is used for debugging
	 */
	if (_keyname.length() == 1) {
		/* Ascii? if so, ez convert to SDLKey instantly.
		 * see SDL_keysym.h for values mapped to SDL keys.
		*/

		int comparekey = _keyname[0];
		int customvalues[6] = {8,9,12,13,19,27};
		if (inrange(comparekey,91,127) || inrange(comparekey, 32, 64) || in(comparekey, customvalues)) { //if valid ascii
			key = (SDLKey)comparekey;
		} else key = SDLK_UNKNOWN;
	} else if (__keymap.find(_keyname) != __keymap.end()) {
		key = __keymap[_keyname];
	} else {
		key = SDLK_UNKNOWN; // == 0
	}
	if (key == SDLK_UNKNOWN)
		std::cerr << "Warning: " << _referencekey << " was not set." << std::endl;
}

bool KeySet::LoadKeysetFromFile(KeySet* _ks, std::string _file)
{
	if (!keymap_setup) SetupKeymap(); //make sure keymap is filled.

	LOG_DEBUG("---PARSING KEYSET FILE---");
	try {
        po::options_description desc;
		desc.add_options()
			("player1.down",  po::value<std::string>()->default_value("\0"), "")
			("player1.up",    po::value<std::string>()->default_value("\0"), "")
			("player1.right", po::value<std::string>()->default_value("\0"), "")
			("player1.left",  po::value<std::string>()->default_value("\0"), "")
			("player1.stop",  po::value<std::string>()->default_value("\0"), "")
			("player2.down",  po::value<std::string>()->default_value("\0"), "")
			("player2.up",    po::value<std::string>()->default_value("\0"), "")
			("player2.right", po::value<std::string>()->default_value("\0"), "")
			("player2.left",  po::value<std::string>()->default_value("\0"), "")
			("player2.stop",  po::value<std::string>()->default_value("\0"), "")
			("player3.down",  po::value<std::string>()->default_value("\0"), "")
			("player3.up",    po::value<std::string>()->default_value("\0"), "")
			("player3.right", po::value<std::string>()->default_value("\0"), "")
			("player3.left",  po::value<std::string>()->default_value("\0"), "")
			("player3.stop",  po::value<std::string>()->default_value("\0"), "")
			("player4.down",  po::value<std::string>()->default_value("\0"), "")
			("player4.up",    po::value<std::string>()->default_value("\0"), "")
			("player4.right", po::value<std::string>()->default_value("\0"), "")
			("player4.left",  po::value<std::string>()->default_value("\0"), "")
			("player4.stop",  po::value<std::string>()->default_value("\0"), "")
			("player1.1.down",  po::value<std::string>(), "")
			("player1.1.up",    po::value<std::string>(), "")
			("player1.1.right", po::value<std::string>(), "")
			("player1.1.left",  po::value<std::string>(), "")
			("player1.1.stop",  po::value<std::string>(), "")
			("player1.2.down",  po::value<std::string>(), "")
			("player1.2.up",    po::value<std::string>(), "")
			("player1.2.right", po::value<std::string>(), "")
			("player1.2.left",  po::value<std::string>(), "")
			("player1.2.stop",  po::value<std::string>(), "")
			("player1.3.down",  po::value<std::string>(), "")
			("player1.3.up",    po::value<std::string>(), "")
			("player1.3.right", po::value<std::string>(), "")
			("player1.3.left",  po::value<std::string>(), "")
			("player1.3.stop",  po::value<std::string>(), "")
			("player1.4.down",  po::value<std::string>(), "")
			("player1.4.up",    po::value<std::string>(), "")
			("player1.4.right", po::value<std::string>(), "")
			("player1.4.left",  po::value<std::string>(), "")
			("player1.4.stop",  po::value<std::string>(), "");
		po::variables_map vm;
		std::ifstream is(_file.c_str());
		po::store(po::parse_config_file(is, desc), vm);
        po::notify(vm);

		//Set keyset for player 1
		setKey(_ks[0].K_DOWN, "player1.down",  vm["player1.down"].as<std::string>());
		setKey(_ks[0].K_UP,   "player1.up",    vm["player1.up"].as<std::string>());
		setKey(_ks[0].K_RIGHT,"player1.right", vm["player1.right"].as<std::string>());
		setKey(_ks[0].K_LEFT, "player1.left",  vm["player1.left"].as<std::string>());
		setKey(_ks[0].K_STOP, "player1.stop",  vm["player1.stop"].as<std::string>());
		//Set keyset for player 2
		setKey(_ks[1].K_DOWN, "player2.down",  vm["player2.down"].as<std::string>());
		setKey(_ks[1].K_UP,   "player2.up",    vm["player2.up"].as<std::string>());
		setKey(_ks[1].K_RIGHT,"player2.right", vm["player2.right"].as<std::string>());
		setKey(_ks[1].K_LEFT, "player2.left",  vm["player2.left"].as<std::string>());
		setKey(_ks[1].K_STOP, "player2.stop",  vm["player2.stop"].as<std::string>());
		//Set keyset for player 3
		setKey(_ks[2].K_DOWN, "player3.down",  vm["player3.down"].as<std::string>());
		setKey(_ks[2].K_UP,   "player3.up",    vm["player3.up"].as<std::string>());
		setKey(_ks[2].K_RIGHT,"player3.right", vm["player3.right"].as<std::string>());
		setKey(_ks[2].K_LEFT, "player3.left",  vm["player3.left"].as<std::string>());
		setKey(_ks[2].K_STOP, "player3.stop",  vm["player3.stop"].as<std::string>());
		//Set keyset for player 4
		setKey(_ks[3].K_DOWN, "player4.down",  vm["player4.down"].as<std::string>());
		setKey(_ks[3].K_UP,   "player4.up",    vm["player4.up"].as<std::string>());
		setKey(_ks[3].K_RIGHT,"player4.right", vm["player4.right"].as<std::string>());
		setKey(_ks[3].K_LEFT, "player4.left",  vm["player4.left"].as<std::string>());
		setKey(_ks[3].K_STOP, "player4.stop",  vm["player4.stop"].as<std::string>());

        if (config::NUM_OF_PLAYERS == 1)
        {
            if (vm.count("player1.1.down" )) setKey(_ks[0].K_DOWN,  "player1.1.down" ,  vm["player1.1.down" ].as<std::string>());
            if (vm.count("player1.1.up"   )) setKey(_ks[0].K_UP,    "player1.1.up"   ,  vm["player1.1.up"   ].as<std::string>());
            if (vm.count("player1.1.right")) setKey(_ks[0].K_RIGHT, "player1.1.right",  vm["player1.1.right"].as<std::string>());
            if (vm.count("player1.1.left" )) setKey(_ks[0].K_LEFT,  "player1.1.left" ,  vm["player1.1.left" ].as<std::string>());
            if (vm.count("player1.1.stop" )) setKey(_ks[0].K_STOP,  "player1.1.stop" ,  vm["player1.1.stop" ].as<std::string>());
            if (vm.count("player2.1.down" )) setKey(_ks[1].K_DOWN,  "player2.1.down" ,  vm["player2.1.down" ].as<std::string>());
            if (vm.count("player2.1.up"   )) setKey(_ks[1].K_UP,    "player2.1.up"   ,  vm["player2.1.up"   ].as<std::string>());
            if (vm.count("player2.1.right")) setKey(_ks[1].K_RIGHT, "player2.1.right",  vm["player2.1.right"].as<std::string>());
            if (vm.count("player2.1.left" )) setKey(_ks[1].K_LEFT,  "player2.1.left" ,  vm["player2.1.left" ].as<std::string>());
            if (vm.count("player2.1.stop" )) setKey(_ks[1].K_STOP,  "player2.1.stop" ,  vm["player2.1.stop" ].as<std::string>());
            if (vm.count("player3.1.down" )) setKey(_ks[2].K_DOWN,  "player3.1.down" ,  vm["player3.1.down" ].as<std::string>());
            if (vm.count("player3.1.up"   )) setKey(_ks[2].K_UP,    "player3.1.up"   ,  vm["player3.1.up"   ].as<std::string>());
            if (vm.count("player3.1.right")) setKey(_ks[2].K_RIGHT, "player3.1.right",  vm["player3.1.right"].as<std::string>());
            if (vm.count("player3.1.left" )) setKey(_ks[2].K_LEFT,  "player3.1.left" ,  vm["player3.1.left" ].as<std::string>());
            if (vm.count("player3.1.stop" )) setKey(_ks[2].K_STOP,  "player3.1.stop" ,  vm["player3.1.stop" ].as<std::string>());
            if (vm.count("player4.1.down" )) setKey(_ks[3].K_DOWN,  "player4.1.down" ,  vm["player4.1.down" ].as<std::string>());
            if (vm.count("player4.1.up"   )) setKey(_ks[3].K_UP,    "player4.1.up"   ,  vm["player4.1.up"   ].as<std::string>());
            if (vm.count("player4.1.right")) setKey(_ks[3].K_RIGHT, "player4.1.right",  vm["player4.1.right"].as<std::string>());
            if (vm.count("player4.1.left" )) setKey(_ks[3].K_LEFT,  "player4.1.left" ,  vm["player4.1.left" ].as<std::string>());
            if (vm.count("player4.1.stop" )) setKey(_ks[3].K_STOP,  "player4.1.stop" ,  vm["player4.1.stop" ].as<std::string>());            
        } else if (config::NUM_OF_PLAYERS == 2)
        {
            if (vm.count("player1.2.down" )) setKey(_ks[0].K_DOWN,  "player1.2.down" ,  vm["player1.2.down" ].as<std::string>());
            if (vm.count("player1.2.up"   )) setKey(_ks[0].K_UP,    "player1.2.up"   ,  vm["player1.2.up"   ].as<std::string>());
            if (vm.count("player1.2.right")) setKey(_ks[0].K_RIGHT, "player1.2.right",  vm["player1.2.right"].as<std::string>());
            if (vm.count("player1.2.left" )) setKey(_ks[0].K_LEFT,  "player1.2.left" ,  vm["player1.2.left" ].as<std::string>());
            if (vm.count("player1.2.stop" )) setKey(_ks[0].K_STOP,  "player1.2.stop" ,  vm["player1.2.stop" ].as<std::string>());
            if (vm.count("player2.2.down" )) setKey(_ks[1].K_DOWN,  "player2.2.down" ,  vm["player2.2.down" ].as<std::string>());
            if (vm.count("player2.2.up"   )) setKey(_ks[1].K_UP,    "player2.2.up"   ,  vm["player2.2.up"   ].as<std::string>());
            if (vm.count("player2.2.right")) setKey(_ks[1].K_RIGHT, "player2.2.right",  vm["player2.2.right"].as<std::string>());
            if (vm.count("player2.2.left" )) setKey(_ks[1].K_LEFT,  "player2.2.left" ,  vm["player2.2.left" ].as<std::string>());
            if (vm.count("player2.2.stop" )) setKey(_ks[1].K_STOP,  "player2.2.stop" ,  vm["player2.2.stop" ].as<std::string>());
            if (vm.count("player3.2.down" )) setKey(_ks[2].K_DOWN,  "player3.2.down" ,  vm["player3.2.down" ].as<std::string>());
            if (vm.count("player3.2.up"   )) setKey(_ks[2].K_UP,    "player3.2.up"   ,  vm["player3.2.up"   ].as<std::string>());
            if (vm.count("player3.2.right")) setKey(_ks[2].K_RIGHT, "player3.2.right",  vm["player3.2.right"].as<std::string>());
            if (vm.count("player3.2.left" )) setKey(_ks[2].K_LEFT,  "player3.2.left" ,  vm["player3.2.left" ].as<std::string>());
            if (vm.count("player3.2.stop" )) setKey(_ks[2].K_STOP,  "player3.2.stop" ,  vm["player3.2.stop" ].as<std::string>());
            if (vm.count("player4.2.down" )) setKey(_ks[3].K_DOWN,  "player4.2.down" ,  vm["player4.2.down" ].as<std::string>());
            if (vm.count("player4.2.up"   )) setKey(_ks[3].K_UP,    "player4.2.up"   ,  vm["player4.2.up"   ].as<std::string>());
            if (vm.count("player4.2.right")) setKey(_ks[3].K_RIGHT, "player4.2.right",  vm["player4.2.right"].as<std::string>());
            if (vm.count("player4.2.left" )) setKey(_ks[3].K_LEFT,  "player4.2.left" ,  vm["player4.2.left" ].as<std::string>());
            if (vm.count("player4.2.stop" )) setKey(_ks[3].K_STOP,  "player4.2.stop" ,  vm["player4.2.stop" ].as<std::string>());            
        } else if (config::NUM_OF_PLAYERS == 3)
        {
            if (vm.count("player1.3.down" )) setKey(_ks[0].K_DOWN,  "player1.3.down" ,  vm["player1.3.down" ].as<std::string>());
            if (vm.count("player1.3.up"   )) setKey(_ks[0].K_UP,    "player1.3.up"   ,  vm["player1.3.up"   ].as<std::string>());
            if (vm.count("player1.3.right")) setKey(_ks[0].K_RIGHT, "player1.3.right",  vm["player1.3.right"].as<std::string>());
            if (vm.count("player1.3.left" )) setKey(_ks[0].K_LEFT,  "player1.3.left" ,  vm["player1.3.left" ].as<std::string>());
            if (vm.count("player1.3.stop" )) setKey(_ks[0].K_STOP,  "player1.3.stop" ,  vm["player1.3.stop" ].as<std::string>());
            if (vm.count("player2.3.down" )) setKey(_ks[1].K_DOWN,  "player2.3.down" ,  vm["player2.3.down" ].as<std::string>());
            if (vm.count("player2.3.up"   )) setKey(_ks[1].K_UP,    "player2.3.up"   ,  vm["player2.3.up"   ].as<std::string>());
            if (vm.count("player2.3.right")) setKey(_ks[1].K_RIGHT, "player2.3.right",  vm["player2.3.right"].as<std::string>());
            if (vm.count("player2.3.left" )) setKey(_ks[1].K_LEFT,  "player2.3.left" ,  vm["player2.3.left" ].as<std::string>());
            if (vm.count("player2.3.stop" )) setKey(_ks[1].K_STOP,  "player2.3.stop" ,  vm["player2.3.stop" ].as<std::string>());
            if (vm.count("player3.3.down" )) setKey(_ks[2].K_DOWN,  "player3.3.down" ,  vm["player3.3.down" ].as<std::string>());
            if (vm.count("player3.3.up"   )) setKey(_ks[2].K_UP,    "player3.3.up"   ,  vm["player3.3.up"   ].as<std::string>());
            if (vm.count("player3.3.right")) setKey(_ks[2].K_RIGHT, "player3.3.right",  vm["player3.3.right"].as<std::string>());
            if (vm.count("player3.3.left" )) setKey(_ks[2].K_LEFT,  "player3.3.left" ,  vm["player3.3.left" ].as<std::string>());
            if (vm.count("player3.3.stop" )) setKey(_ks[2].K_STOP,  "player3.3.stop" ,  vm["player3.3.stop" ].as<std::string>());
            if (vm.count("player4.3.down" )) setKey(_ks[3].K_DOWN,  "player4.3.down" ,  vm["player4.3.down" ].as<std::string>());
            if (vm.count("player4.3.up"   )) setKey(_ks[3].K_UP,    "player4.3.up"   ,  vm["player4.3.up"   ].as<std::string>());
            if (vm.count("player4.3.right")) setKey(_ks[3].K_RIGHT, "player4.3.right",  vm["player4.3.right"].as<std::string>());
            if (vm.count("player4.3.left" )) setKey(_ks[3].K_LEFT,  "player4.3.left" ,  vm["player4.3.left" ].as<std::string>());
            if (vm.count("player4.3.stop" )) setKey(_ks[3].K_STOP,  "player4.3.stop" ,  vm["player4.3.stop" ].as<std::string>());            
        } else if (config::NUM_OF_PLAYERS == 3)
        {
            if (vm.count("player1.4.down" )) setKey(_ks[0].K_DOWN,  "player1.4.down" ,  vm["player1.4.down" ].as<std::string>());
            if (vm.count("player1.4.up"   )) setKey(_ks[0].K_UP,    "player1.4.up"   ,  vm["player1.4.up"   ].as<std::string>());
            if (vm.count("player1.4.right")) setKey(_ks[0].K_RIGHT, "player1.4.right",  vm["player1.4.right"].as<std::string>());
            if (vm.count("player1.4.left" )) setKey(_ks[0].K_LEFT,  "player1.4.left" ,  vm["player1.4.left" ].as<std::string>());
            if (vm.count("player1.4.stop" )) setKey(_ks[0].K_STOP,  "player1.4.stop" ,  vm["player1.4.stop" ].as<std::string>());
            if (vm.count("player2.4.down" )) setKey(_ks[1].K_DOWN,  "player2.4.down" ,  vm["player2.4.down" ].as<std::string>());
            if (vm.count("player2.4.up"   )) setKey(_ks[1].K_UP,    "player2.4.up"   ,  vm["player2.4.up"   ].as<std::string>());
            if (vm.count("player2.4.right")) setKey(_ks[1].K_RIGHT, "player2.4.right",  vm["player2.4.right"].as<std::string>());
            if (vm.count("player2.4.left" )) setKey(_ks[1].K_LEFT,  "player2.4.left" ,  vm["player2.4.left" ].as<std::string>());
            if (vm.count("player2.4.stop" )) setKey(_ks[1].K_STOP,  "player2.4.stop" ,  vm["player2.4.stop" ].as<std::string>());
            if (vm.count("player3.4.down" )) setKey(_ks[2].K_DOWN,  "player3.4.down" ,  vm["player3.4.down" ].as<std::string>());
            if (vm.count("player3.4.up"   )) setKey(_ks[2].K_UP,    "player3.4.up"   ,  vm["player3.4.up"   ].as<std::string>());
            if (vm.count("player3.4.right")) setKey(_ks[2].K_RIGHT, "player3.4.right",  vm["player3.4.right"].as<std::string>());
            if (vm.count("player3.4.left" )) setKey(_ks[2].K_LEFT,  "player3.4.left" ,  vm["player3.4.left" ].as<std::string>());
            if (vm.count("player3.4.stop" )) setKey(_ks[2].K_STOP,  "player3.4.stop" ,  vm["player3.4.stop" ].as<std::string>());
            if (vm.count("player4.4.down" )) setKey(_ks[3].K_DOWN,  "player4.4.down" ,  vm["player4.4.down" ].as<std::string>());
            if (vm.count("player4.4.up"   )) setKey(_ks[3].K_UP,    "player4.4.up"   ,  vm["player4.4.up"   ].as<std::string>());
            if (vm.count("player4.4.right")) setKey(_ks[3].K_RIGHT, "player4.4.right",  vm["player4.4.right"].as<std::string>());
            if (vm.count("player4.4.left" )) setKey(_ks[3].K_LEFT,  "player4.4.left" ,  vm["player4.4.left" ].as<std::string>());
            if (vm.count("player4.4.stop" )) setKey(_ks[3].K_STOP,  "player4.4.stop" ,  vm["player4.4.stop" ].as<std::string>());            
        }
	} catch (boost::program_options::error &e) {
        std::cerr << "error parsing keyset file: \"" << _file << "\". Error: " << e.what() << std::endl;
		return false;
    } catch (...) {
        std::cerr << "unknown exception" << std::endl;
		return false;
    }
	LOG_DEBUG("---PARSING KEYSETS DONE!---");
	return true;
}