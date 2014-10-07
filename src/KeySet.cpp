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


#include "KeySet.hpp"
#include "Gameconfig.hpp"
#include "Log.hpp"
#include <fstream>
#include "GameEngine.hpp"

#include <LuaBridge\LuaBridge.h>


std::map<std::string, SDL_Keycode> KeySet::__keymap;
bool KeySet::keymap_setup = false;

void KeySet::SetupKeymap()
{
    LOG_DEBUG << "Setting up keymap...\n";
    __keymap["up"] = SDLK_UP;
    __keymap["down"] = SDLK_DOWN;
    __keymap["left"] = SDLK_LEFT;
    __keymap["right"] = SDLK_RIGHT;
    __keymap["num_1"] = SDLK_KP_1;
    __keymap["num_2"] = SDLK_KP_2;
    __keymap["num_3"] = SDLK_KP_3;
    __keymap["num_4"] = SDLK_KP_4;
    __keymap["num_5"] = SDLK_KP_5;
    __keymap["num_6"] = SDLK_KP_6;
    __keymap["num_7"] = SDLK_KP_7;
    __keymap["num_8"] = SDLK_KP_8;
    __keymap["num_9"] = SDLK_KP_9;
    __keymap["num_0"] = SDLK_KP_0;
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
    for (int i = 0; i < sizeof(list); i++)  if (x == list[i]) return true;
    return false;
}

void KeySet::setKey(SDL_Keycode& key, std::string _referencekey, std::string _keyname) 
{
    /* Sets key to selected key in keymap
     * Defaults to SDLK_UNKNOWN if no key found in keymap or in Ascii table
     * Referencekey is used for debugging
     */
    if (_keyname.length() == 1) {
        /* Ascii? if so, ez convert to SDL_Keysym instantly.
         * see SDL_keysym.h for values mapped to SDL keys.
        */

        int comparekey = _keyname[0];
        int customvalues[6] = {8,9,12,13,19,27};
        if (inrange(comparekey,91,127) || inrange(comparekey, 32, 64) || in(comparekey, customvalues)) { //if valid ascii
            key = comparekey;
        } else key = SDLK_UNKNOWN;
    } else if (__keymap.find(_keyname) != __keymap.end()) {
        key = __keymap[_keyname];
    } else {
        key = SDLK_UNKNOWN; // == 0
    }
    if (key == SDLK_UNKNOWN)
        LOG_ERROR << "Warning: " << _referencekey << " was not set.\n";
}

bool KeySet::LoadKeysetFromLuaFile(KeySet* _ks, std::string _file) {
	_file = config::path + _file + ".lua";
	lua_State* L = GameEngine::LuaState;
	if (luaL_loadfile(L, _file.c_str())) {
		LOG_ERROR << "Couldn't read keysets from file " << _file << std::endl;
	}
	if (lua_pcall(L, 0, 0, 0)) {
		LOG_ERROR << "Error calling keysets file" << std::endl;
	}

	luabridge::LuaRef keysets = luabridge::getGlobal(L, "keysets");
	if (keysets.isNil()) return false;

	//Set keyset for player 1
	luabridge::LuaRef player1Keysets = keysets["player1"];
	if (player1Keysets.isNil()) return false;
	setKey(_ks[0].K_DOWN, "player1.down", player1Keysets["down"].cast<std::string>());
	setKey(_ks[0].K_UP, "player1.up", player1Keysets["up"].cast<std::string>());
	setKey(_ks[0].K_RIGHT, "player1.right", player1Keysets["right"].cast<std::string>());
	setKey(_ks[0].K_LEFT, "player1.left", player1Keysets["left"].cast<std::string>());
	setKey(_ks[0].K_STOP, "player1.stop", player1Keysets["stop"].cast<std::string>());
	if (config::NUM_OF_PLAYERS == 1) {
		if (!player1Keysets["one"].isNil()) {
			luabridge::LuaRef ref = player1Keysets["one"];
			if (!ref.isNil()) {
				setKey(_ks[0].K_STOP, "player1.stop", ref["stop"].cast<std::string>());
			}
		}
	}

	//Set keyset for player 2
	luabridge::LuaRef player2Keysets = keysets["player2"];
	if (player2Keysets.isNil()) return false;
	setKey(_ks[1].K_DOWN, "player2.down", player2Keysets["down"].cast<std::string>());
	setKey(_ks[1].K_UP, "player2.up", player2Keysets["up"].cast<std::string>());
	setKey(_ks[1].K_RIGHT, "player2.right", player2Keysets["right"].cast<std::string>());
	setKey(_ks[1].K_LEFT, "player2.left", player2Keysets["left"].cast<std::string>());
	setKey(_ks[1].K_STOP, "player2.stop", player2Keysets["stop"].cast<std::string>());
	//	//Set keyset for player 3
	luabridge::LuaRef player3Keysets = keysets["player3"];
	if (player3Keysets.isNil()) return false;
	setKey(_ks[2].K_DOWN, "player3.down", player3Keysets["down"].cast<std::string>());
	setKey(_ks[2].K_UP, "player3.up", player3Keysets["up"].cast<std::string>());
	setKey(_ks[2].K_RIGHT, "player3.right", player3Keysets["right"].cast<std::string>());
	setKey(_ks[2].K_LEFT, "player3.left", player3Keysets["left"].cast<std::string>());
	setKey(_ks[2].K_STOP, "player3.stop", player3Keysets["stop"].cast<std::string>());
	//	//Set keyset for player 4
	luabridge::LuaRef player4Keysets = keysets["player4"];
	if (player4Keysets.isNil()) return false;
	setKey(_ks[3].K_DOWN, "player4.down", player4Keysets["down"].cast<std::string>());
	setKey(_ks[3].K_UP, "player4.up", player4Keysets["up"].cast<std::string>());
	setKey(_ks[3].K_RIGHT, "player4.right", player4Keysets["right"].cast<std::string>());
	setKey(_ks[3].K_LEFT, "player4.left", player4Keysets["left"].cast<std::string>());
	setKey(_ks[3].K_STOP, "player4.stop", player4Keysets["stop"].cast<std::string>());

	return true;
}

bool KeySet::LoadKeysetFromFile(KeySet* _ks, std::string _file)
{
    if (!keymap_setup) SetupKeymap(); //make sure keymap is filled.

    LOG_DEBUG << "---PARSING KEYSET FILE---\n";
	return LoadKeysetFromLuaFile(_ks, _file);
//    try {
//        po::options_description desc;
//        desc.add_options()
//            ("player1.down",  po::value<std::string>()->default_value("\0"), "")
//            ("player1.up",    po::value<std::string>()->default_value("\0"), "")
//            ("player1.right", po::value<std::string>()->default_value("\0"), "")
//            ("player1.left",  po::value<std::string>()->default_value("\0"), "")
//            ("player1.stop",  po::value<std::string>()->default_value("\0"), "")
//            ("player2.down",  po::value<std::string>()->default_value("\0"), "")
//            ("player2.up",    po::value<std::string>()->default_value("\0"), "")
//            ("player2.right", po::value<std::string>()->default_value("\0"), "")
//            ("player2.left",  po::value<std::string>()->default_value("\0"), "")
//            ("player2.stop",  po::value<std::string>()->default_value("\0"), "")
//            ("player3.down",  po::value<std::string>()->default_value("\0"), "")
//            ("player3.up",    po::value<std::string>()->default_value("\0"), "")
//            ("player3.right", po::value<std::string>()->default_value("\0"), "")
//            ("player3.left",  po::value<std::string>()->default_value("\0"), "")
//            ("player3.stop",  po::value<std::string>()->default_value("\0"), "")
//            ("player4.down",  po::value<std::string>()->default_value("\0"), "")
//            ("player4.up",    po::value<std::string>()->default_value("\0"), "")
//            ("player4.right", po::value<std::string>()->default_value("\0"), "")
//            ("player4.left",  po::value<std::string>()->default_value("\0"), "")
//            ("player4.stop",  po::value<std::string>()->default_value("\0"), "")
//            ("player1.1.down",  po::value<std::string>(), "")
//            ("player1.1.up",    po::value<std::string>(), "")
//            ("player1.1.right", po::value<std::string>(), "")
//            ("player1.1.left",  po::value<std::string>(), "")
//            ("player1.1.stop",  po::value<std::string>(), "")
//            ("player1.2.down",  po::value<std::string>(), "")
//            ("player1.2.up",    po::value<std::string>(), "")
//            ("player1.2.right", po::value<std::string>(), "")
//            ("player1.2.left",  po::value<std::string>(), "")
//            ("player1.2.stop",  po::value<std::string>(), "")
//            ("player1.3.down",  po::value<std::string>(), "")
//            ("player1.3.up",    po::value<std::string>(), "")
//            ("player1.3.right", po::value<std::string>(), "")
//            ("player1.3.left",  po::value<std::string>(), "")
//            ("player1.3.stop",  po::value<std::string>(), "")
//            ("player1.4.down",  po::value<std::string>(), "")
//            ("player1.4.up",    po::value<std::string>(), "")
//            ("player1.4.right", po::value<std::string>(), "")
//            ("player1.4.left",  po::value<std::string>(), "")
//            ("player1.4.stop",  po::value<std::string>(), "");
//        po::variables_map vm;
//        std::ifstream is((config::path + _file).c_str());
//        po::store(po::parse_config_file(is, desc), vm);
//        po::notify(vm);
//
//        //Set keyset for player 1
//        setKey(_ks[0].K_DOWN, "player1.down",  vm["player1.down"].as<std::string>());
//        setKey(_ks[0].K_UP,   "player1.up",    vm["player1.up"].as<std::string>());
//        setKey(_ks[0].K_RIGHT,"player1.right", vm["player1.right"].as<std::string>());
//        setKey(_ks[0].K_LEFT, "player1.left",  vm["player1.left"].as<std::string>());
//        setKey(_ks[0].K_STOP, "player1.stop",  vm["player1.stop"].as<std::string>());
//        //Set keyset for player 2
//        setKey(_ks[1].K_DOWN, "player2.down",  vm["player2.down"].as<std::string>());
//        setKey(_ks[1].K_UP,   "player2.up",    vm["player2.up"].as<std::string>());
//        setKey(_ks[1].K_RIGHT,"player2.right", vm["player2.right"].as<std::string>());
//        setKey(_ks[1].K_LEFT, "player2.left",  vm["player2.left"].as<std::string>());
//        setKey(_ks[1].K_STOP, "player2.stop",  vm["player2.stop"].as<std::string>());
//        //Set keyset for player 3
//        setKey(_ks[2].K_DOWN, "player3.down",  vm["player3.down"].as<std::string>());
//        setKey(_ks[2].K_UP,   "player3.up",    vm["player3.up"].as<std::string>());
//        setKey(_ks[2].K_RIGHT,"player3.right", vm["player3.right"].as<std::string>());
//        setKey(_ks[2].K_LEFT, "player3.left",  vm["player3.left"].as<std::string>());
//        setKey(_ks[2].K_STOP, "player3.stop",  vm["player3.stop"].as<std::string>());
//        //Set keyset for player 4
//        setKey(_ks[3].K_DOWN, "player4.down",  vm["player4.down"].as<std::string>());
//        setKey(_ks[3].K_UP,   "player4.up",    vm["player4.up"].as<std::string>());
//        setKey(_ks[3].K_RIGHT,"player4.right", vm["player4.right"].as<std::string>());
//        setKey(_ks[3].K_LEFT, "player4.left",  vm["player4.left"].as<std::string>());
//        setKey(_ks[3].K_STOP, "player4.stop",  vm["player4.stop"].as<std::string>());
//
//        if (config::NUM_OF_PLAYERS == 1)
//        {
//            if (vm.count("player1.1.down" )) setKey(_ks[0].K_DOWN,  "player1.1.down" ,  vm["player1.1.down" ].as<std::string>());
//            if (vm.count("player1.1.up"   )) setKey(_ks[0].K_UP,    "player1.1.up"   ,  vm["player1.1.up"   ].as<std::string>());
//            if (vm.count("player1.1.right")) setKey(_ks[0].K_RIGHT, "player1.1.right",  vm["player1.1.right"].as<std::string>());
//            if (vm.count("player1.1.left" )) setKey(_ks[0].K_LEFT,  "player1.1.left" ,  vm["player1.1.left" ].as<std::string>());
//            if (vm.count("player1.1.stop" )) setKey(_ks[0].K_STOP,  "player1.1.stop" ,  vm["player1.1.stop" ].as<std::string>());
//            if (vm.count("player2.1.down" )) setKey(_ks[1].K_DOWN,  "player2.1.down" ,  vm["player2.1.down" ].as<std::string>());
//            if (vm.count("player2.1.up"   )) setKey(_ks[1].K_UP,    "player2.1.up"   ,  vm["player2.1.up"   ].as<std::string>());
//            if (vm.count("player2.1.right")) setKey(_ks[1].K_RIGHT, "player2.1.right",  vm["player2.1.right"].as<std::string>());
//            if (vm.count("player2.1.left" )) setKey(_ks[1].K_LEFT,  "player2.1.left" ,  vm["player2.1.left" ].as<std::string>());
//            if (vm.count("player2.1.stop" )) setKey(_ks[1].K_STOP,  "player2.1.stop" ,  vm["player2.1.stop" ].as<std::string>());
//            if (vm.count("player3.1.down" )) setKey(_ks[2].K_DOWN,  "player3.1.down" ,  vm["player3.1.down" ].as<std::string>());
//            if (vm.count("player3.1.up"   )) setKey(_ks[2].K_UP,    "player3.1.up"   ,  vm["player3.1.up"   ].as<std::string>());
//            if (vm.count("player3.1.right")) setKey(_ks[2].K_RIGHT, "player3.1.right",  vm["player3.1.right"].as<std::string>());
//            if (vm.count("player3.1.left" )) setKey(_ks[2].K_LEFT,  "player3.1.left" ,  vm["player3.1.left" ].as<std::string>());
//            if (vm.count("player3.1.stop" )) setKey(_ks[2].K_STOP,  "player3.1.stop" ,  vm["player3.1.stop" ].as<std::string>());
//            if (vm.count("player4.1.down" )) setKey(_ks[3].K_DOWN,  "player4.1.down" ,  vm["player4.1.down" ].as<std::string>());
//            if (vm.count("player4.1.up"   )) setKey(_ks[3].K_UP,    "player4.1.up"   ,  vm["player4.1.up"   ].as<std::string>());
//            if (vm.count("player4.1.right")) setKey(_ks[3].K_RIGHT, "player4.1.right",  vm["player4.1.right"].as<std::string>());
//            if (vm.count("player4.1.left" )) setKey(_ks[3].K_LEFT,  "player4.1.left" ,  vm["player4.1.left" ].as<std::string>());
//            if (vm.count("player4.1.stop" )) setKey(_ks[3].K_STOP,  "player4.1.stop" ,  vm["player4.1.stop" ].as<std::string>());
//        } else if (config::NUM_OF_PLAYERS == 2)
//        {
//            if (vm.count("player1.2.down" )) setKey(_ks[0].K_DOWN,  "player1.2.down" ,  vm["player1.2.down" ].as<std::string>());
//            if (vm.count("player1.2.up"   )) setKey(_ks[0].K_UP,    "player1.2.up"   ,  vm["player1.2.up"   ].as<std::string>());
//            if (vm.count("player1.2.right")) setKey(_ks[0].K_RIGHT, "player1.2.right",  vm["player1.2.right"].as<std::string>());
//            if (vm.count("player1.2.left" )) setKey(_ks[0].K_LEFT,  "player1.2.left" ,  vm["player1.2.left" ].as<std::string>());
//            if (vm.count("player1.2.stop" )) setKey(_ks[0].K_STOP,  "player1.2.stop" ,  vm["player1.2.stop" ].as<std::string>());
//            if (vm.count("player2.2.down" )) setKey(_ks[1].K_DOWN,  "player2.2.down" ,  vm["player2.2.down" ].as<std::string>());
//            if (vm.count("player2.2.up"   )) setKey(_ks[1].K_UP,    "player2.2.up"   ,  vm["player2.2.up"   ].as<std::string>());
//            if (vm.count("player2.2.right")) setKey(_ks[1].K_RIGHT, "player2.2.right",  vm["player2.2.right"].as<std::string>());
//            if (vm.count("player2.2.left" )) setKey(_ks[1].K_LEFT,  "player2.2.left" ,  vm["player2.2.left" ].as<std::string>());
//            if (vm.count("player2.2.stop" )) setKey(_ks[1].K_STOP,  "player2.2.stop" ,  vm["player2.2.stop" ].as<std::string>());
//            if (vm.count("player3.2.down" )) setKey(_ks[2].K_DOWN,  "player3.2.down" ,  vm["player3.2.down" ].as<std::string>());
//            if (vm.count("player3.2.up"   )) setKey(_ks[2].K_UP,    "player3.2.up"   ,  vm["player3.2.up"   ].as<std::string>());
//            if (vm.count("player3.2.right")) setKey(_ks[2].K_RIGHT, "player3.2.right",  vm["player3.2.right"].as<std::string>());
//            if (vm.count("player3.2.left" )) setKey(_ks[2].K_LEFT,  "player3.2.left" ,  vm["player3.2.left" ].as<std::string>());
//            if (vm.count("player3.2.stop" )) setKey(_ks[2].K_STOP,  "player3.2.stop" ,  vm["player3.2.stop" ].as<std::string>());
//            if (vm.count("player4.2.down" )) setKey(_ks[3].K_DOWN,  "player4.2.down" ,  vm["player4.2.down" ].as<std::string>());
//            if (vm.count("player4.2.up"   )) setKey(_ks[3].K_UP,    "player4.2.up"   ,  vm["player4.2.up"   ].as<std::string>());
//            if (vm.count("player4.2.right")) setKey(_ks[3].K_RIGHT, "player4.2.right",  vm["player4.2.right"].as<std::string>());
//            if (vm.count("player4.2.left" )) setKey(_ks[3].K_LEFT,  "player4.2.left" ,  vm["player4.2.left" ].as<std::string>());
//            if (vm.count("player4.2.stop" )) setKey(_ks[3].K_STOP,  "player4.2.stop" ,  vm["player4.2.stop" ].as<std::string>());
//        } else if (config::NUM_OF_PLAYERS == 3)
//        {
//            if (vm.count("player1.3.down" )) setKey(_ks[0].K_DOWN,  "player1.3.down" ,  vm["player1.3.down" ].as<std::string>());
//            if (vm.count("player1.3.up"   )) setKey(_ks[0].K_UP,    "player1.3.up"   ,  vm["player1.3.up"   ].as<std::string>());
//            if (vm.count("player1.3.right")) setKey(_ks[0].K_RIGHT, "player1.3.right",  vm["player1.3.right"].as<std::string>());
//            if (vm.count("player1.3.left" )) setKey(_ks[0].K_LEFT,  "player1.3.left" ,  vm["player1.3.left" ].as<std::string>());
//            if (vm.count("player1.3.stop" )) setKey(_ks[0].K_STOP,  "player1.3.stop" ,  vm["player1.3.stop" ].as<std::string>());
//            if (vm.count("player2.3.down" )) setKey(_ks[1].K_DOWN,  "player2.3.down" ,  vm["player2.3.down" ].as<std::string>());
//            if (vm.count("player2.3.up"   )) setKey(_ks[1].K_UP,    "player2.3.up"   ,  vm["player2.3.up"   ].as<std::string>());
//            if (vm.count("player2.3.right")) setKey(_ks[1].K_RIGHT, "player2.3.right",  vm["player2.3.right"].as<std::string>());
//            if (vm.count("player2.3.left" )) setKey(_ks[1].K_LEFT,  "player2.3.left" ,  vm["player2.3.left" ].as<std::string>());
//            if (vm.count("player2.3.stop" )) setKey(_ks[1].K_STOP,  "player2.3.stop" ,  vm["player2.3.stop" ].as<std::string>());
//            if (vm.count("player3.3.down" )) setKey(_ks[2].K_DOWN,  "player3.3.down" ,  vm["player3.3.down" ].as<std::string>());
//            if (vm.count("player3.3.up"   )) setKey(_ks[2].K_UP,    "player3.3.up"   ,  vm["player3.3.up"   ].as<std::string>());
//            if (vm.count("player3.3.right")) setKey(_ks[2].K_RIGHT, "player3.3.right",  vm["player3.3.right"].as<std::string>());
//            if (vm.count("player3.3.left" )) setKey(_ks[2].K_LEFT,  "player3.3.left" ,  vm["player3.3.left" ].as<std::string>());
//            if (vm.count("player3.3.stop" )) setKey(_ks[2].K_STOP,  "player3.3.stop" ,  vm["player3.3.stop" ].as<std::string>());
//            if (vm.count("player4.3.down" )) setKey(_ks[3].K_DOWN,  "player4.3.down" ,  vm["player4.3.down" ].as<std::string>());
//            if (vm.count("player4.3.up"   )) setKey(_ks[3].K_UP,    "player4.3.up"   ,  vm["player4.3.up"   ].as<std::string>());
//            if (vm.count("player4.3.right")) setKey(_ks[3].K_RIGHT, "player4.3.right",  vm["player4.3.right"].as<std::string>());
//            if (vm.count("player4.3.left" )) setKey(_ks[3].K_LEFT,  "player4.3.left" ,  vm["player4.3.left" ].as<std::string>());
//            if (vm.count("player4.3.stop" )) setKey(_ks[3].K_STOP,  "player4.3.stop" ,  vm["player4.3.stop" ].as<std::string>());
//        } else if (config::NUM_OF_PLAYERS == 3)
//        {
//            if (vm.count("player1.4.down" )) setKey(_ks[0].K_DOWN,  "player1.4.down" ,  vm["player1.4.down" ].as<std::string>());
//            if (vm.count("player1.4.up"   )) setKey(_ks[0].K_UP,    "player1.4.up"   ,  vm["player1.4.up"   ].as<std::string>());
//            if (vm.count("player1.4.right")) setKey(_ks[0].K_RIGHT, "player1.4.right",  vm["player1.4.right"].as<std::string>());
//            if (vm.count("player1.4.left" )) setKey(_ks[0].K_LEFT,  "player1.4.left" ,  vm["player1.4.left" ].as<std::string>());
//            if (vm.count("player1.4.stop" )) setKey(_ks[0].K_STOP,  "player1.4.stop" ,  vm["player1.4.stop" ].as<std::string>());
//            if (vm.count("player2.4.down" )) setKey(_ks[1].K_DOWN,  "player2.4.down" ,  vm["player2.4.down" ].as<std::string>());
//            if (vm.count("player2.4.up"   )) setKey(_ks[1].K_UP,    "player2.4.up"   ,  vm["player2.4.up"   ].as<std::string>());
//            if (vm.count("player2.4.right")) setKey(_ks[1].K_RIGHT, "player2.4.right",  vm["player2.4.right"].as<std::string>());
//            if (vm.count("player2.4.left" )) setKey(_ks[1].K_LEFT,  "player2.4.left" ,  vm["player2.4.left" ].as<std::string>());
//            if (vm.count("player2.4.stop" )) setKey(_ks[1].K_STOP,  "player2.4.stop" ,  vm["player2.4.stop" ].as<std::string>());
//            if (vm.count("player3.4.down" )) setKey(_ks[2].K_DOWN,  "player3.4.down" ,  vm["player3.4.down" ].as<std::string>());
//            if (vm.count("player3.4.up"   )) setKey(_ks[2].K_UP,    "player3.4.up"   ,  vm["player3.4.up"   ].as<std::string>());
//            if (vm.count("player3.4.right")) setKey(_ks[2].K_RIGHT, "player3.4.right",  vm["player3.4.right"].as<std::string>());
//            if (vm.count("player3.4.left" )) setKey(_ks[2].K_LEFT,  "player3.4.left" ,  vm["player3.4.left" ].as<std::string>());
//            if (vm.count("player3.4.stop" )) setKey(_ks[2].K_STOP,  "player3.4.stop" ,  vm["player3.4.stop" ].as<std::string>());
//            if (vm.count("player4.4.down" )) setKey(_ks[3].K_DOWN,  "player4.4.down" ,  vm["player4.4.down" ].as<std::string>());
//            if (vm.count("player4.4.up"   )) setKey(_ks[3].K_UP,    "player4.4.up"   ,  vm["player4.4.up"   ].as<std::string>());
//            if (vm.count("player4.4.right")) setKey(_ks[3].K_RIGHT, "player4.4.right",  vm["player4.4.right"].as<std::string>());
//            if (vm.count("player4.4.left" )) setKey(_ks[3].K_LEFT,  "player4.4.left" ,  vm["player4.4.left" ].as<std::string>());
//            if (vm.count("player4.4.stop" )) setKey(_ks[3].K_STOP,  "player4.4.stop" ,  vm["player4.4.stop" ].as<std::string>());
//        }
//    } catch (boost::program_options::error &e) {
//        LOG_ERROR << "error parsing keyset file: \"" << _file << "\". Error: " << e.what() << "\n";
//        return false;
//    } catch (...) {
//        LOG_ERROR << "unknown exception\n";
//        return false;
//    }
//    LOG_DEBUG << "---PARSING KEYSETS DONE!---\n";
//    return true;
}
