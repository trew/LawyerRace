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


#include "Gameconfig.hpp"
#include "KeySet.hpp"
#include "Filesystem.hpp"
#include <iostream>
#include <fstream>
#include "Log.hpp"

#include "GameEngine.hpp"

#include <LuaBridge\LuaBridge.h>

namespace config
{
    bool parseConfigFile(std::string _file) {
        LOG_DEBUG << "---PARSING CONFIG---\n";

		lua_State* L = GameEngine::LuaState;
		if (luaL_loadfile(L, _file.c_str())) {
			LOG_ERROR << "Couldn't read config file " << _file << std::endl;
			return false;
		}
		if (lua_pcall(L, 0, 0, 0)) {
			LOG_ERROR << "Error calling config file " << _file << std::endl;
		}

		using namespace luabridge;

		LuaRef config = getGlobal(L, "config");
		if (config.isTable()) {

			if (config["max_enemies"].isNumber())
				config::MAX_ENEMIES = config["max_enemies"].cast<int>();
			if (config["enemies_before_rock"].isNumber())
				config::ENEMIES_BEFORE_ROCK = config["enemies_before_rock"].cast<int>();
			if (config["max_rocks"].isNumber())
				config::MAX_ROCKS = config["max_rocks"].cast<int>();

			LuaRef velocity = config["velocity"];
			if (velocity.isTable()) {
				if (velocity["gamespeed"].isNumber())
					config::GAME_SPEED = velocity["gamespeed"].cast<float>();
				if (velocity["player"].isNumber())
					config::P_VELOCITY = velocity["player"].cast<float>();
				if (velocity["enemy"].isNumber())
					config::E_VELOCITY = velocity["enemy"].cast<float>();

				LuaRef rocks = velocity["rocks"];
				if (rocks.isTable()) {
					if (rocks["small"].isNumber())
						config::R_VELOCITY[0] = rocks["small"].cast<float>();
					if (rocks["medium"].isNumber())
						config::R_VELOCITY[1] = rocks["medium"].cast<float>();
					if (rocks["large"].isNumber())
						config::R_VELOCITY[2] = rocks["large"].cast<float>();
				}
			}

			LuaRef system = config["system"];
			if (system.isTable()) {
				if (system["resolution_width"].isNumber() && system["resolution_height"].isNumber()) {
					config::W_WIDTH = system["resolution_width"].cast<int>();
					config::W_HEIGHT = system["resolution_height"].cast<int>();
				}
			}
		}
		LOG_DEBUG << "---PARSING CONFIG DONE!---\n";
        return true;
    }

    std::string validateConfigFile(std::string _file)
    {
		if (filesys::file_exists(config::path + _file)) {
			LOG_DEBUG << "Using config: " << _file << "\n";
		} else if (filesys::file_exists(config::path + "cfg/" + _file)) {
			_file = "cfg/" + _file;
			LOG_DEBUG << "Using config: " << _file << "\n";
		} else {
            LOG_ERROR << "Error finding config: \"" << _file << "\". Instead using \"" << config::config_file << "\".\n";
            return config::config_file;
        }
        return _file;
    }

    std::string validatePath(std::string _path) {
        std::string path;
        if (filesys::file_exists(_path))
        {
            path = _path;
            LOG_DEBUG << "Using path: " << path << "\n";
        } else {
            path = filesys::get_cwd();
            LOG_ERROR << "Loading Path. \"" << _path << "\". Using \"" << path << "\".\n";
        }
        if (*path.rbegin() != '/')
            path.append("/");
        return path;
    }

    std::string path = ""; // reloaded during command line parsing
    std::string config_file = "cfg/ez.lua"; //standard
    std::string keyset_file = "cfg/keysets.lua"; //standard

    const std::string WINDOW_TEXT = "Lawyer Race";
    int W_WIDTH = 1024; ///<Window Width
    int W_HEIGHT = 768; ///<Window Height

    const int W_BPP = 32;       ///<Window Depth

    const int MAXNUM_OF_PLAYERS = 4; ///< Maximum amount of players that the game supports
    int NUM_OF_PLAYERS = 1;

    const float P_WIDTH = 30;     ///<Size of Player sprite width
    const float P_HEIGHT = 30;    ///<Size of Player sprite height
    const std::string P_SRC[4] = {"player1", "player2",
                                    "player3", "player4" };

    const float E_WIDTH = 30;     ///<Size of Enemy sprite width
    const float E_HEIGHT = 30;    ///<Size of Enemy sprite height
    const std::string E_SRC = "enemyx30";

    const float D_WIDTH = 30;     ///<Size of Dollar sprite width
    const float D_HEIGHT = 15;    ///<Size of Dollar sprite height
    const std::string D_SRC = "dollar";

    const int MAX_R_WIDTH = 58;
    const int MAX_R_HEIGHT = 49;

    const int R_WIDTH[3] = {17, 26, 58};
    const int R_HEIGHT[3] = {14, 25, 49};
    const std::string R_SRC[3] = {"stone1-17x14", "stone2-26x25", "stone3-58x49"};

    bool PLAYER_STOP_ENABLED = true;
    bool OLD_DIAGONAL_SPEED = false; //see enemy movement phase in Enemy.cpp
    int MAX_ENEMIES = 5;
    int ENEMIES_BEFORE_ROCK = 3;
    int MAX_ROCKS = 10;

	float GAME_SPEED = 1.0f;        ///< Gamespeed, configurable in config file
    float P_VELOCITY = 250.0f;        ///< Player velocity
    float E_VELOCITY = 100.0f;        ///< Enemy velocity

	float R_VELOCITY[3] = { 250.f, 187.f, 125.f }; //Rock velocities

    KeySet KEYSET[4];

	bool ENABLE_LERP = true;
	int MAX_FRAMESKIP = 10;
} //namespace config
