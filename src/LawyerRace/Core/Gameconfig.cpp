#include <LawyerEngine/LawyerEngine.hpp>
#include <LawyerRace/Core/LawyerRace.hpp>
#include <LawyerRace/Core/Gameconfig.hpp>
#include <LawyerRace/Core/KeySet.hpp>
#include <iostream>
#include <fstream>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>

namespace config
{
    bool parseConfigFile(std::string _file) {
    LOG_DEBUG("---PARSING CONFIG---");

		lua_State* L = LawyerRace::LuaState;
		LOG_DEBUG("Reading \"%s\"", _file);
		if (luaL_loadfile(L, _file.c_str())) {
			LOG_ERROR("Couldn't read config file %s", _file);
			return false;
		}
		if (lua_pcall(L, 0, 0, 0)) {
			LOG_ERROR("Error calling config file %s", _file);
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

			if (config["skip_menu"].isBool())
				config::SKIP_MENU = config["skip_menu"].cast<bool>();
		}
		LOG_DEBUG("---PARSING CONFIG DONE!---");
        return true;
    }

    std::string validateConfigFile(std::string _file)
    {
		if (lwe::filesys::fileExists(config::path + _file)) {
			LOG_DEBUG("Using config: %s", _file.c_str());
		} else if (lwe::filesys::fileExists(config::path + "cfg/" + _file)) {
			_file = "cfg/" + _file;
			LOG_DEBUG("Using config: %s",_file.c_str());
		} else {
            LOG_ERROR("Error finding config: [%s]. Instead using [%s].", _file.c_str(), config::config_file.c_str());
            return config::config_file;
        }
        return _file;
    }

    std::string validatePath(std::string _path) {
        std::string path;
        if (lwe::filesys::fileExists(_path))
        {
            path = _path;
            LOG_DEBUG("Using path: %s", path.c_str());
        } else {
            path = lwe::filesys::cwd();
            LOG_ERROR("Loading Path [%s] failed. Using [%s].", _path.c_str(), path.c_str());
        }
        if (*path.rbegin() != '/')
            path.append("/");
        return path;
    }

    std::string path = ""; // reloaded during command line parsing
    std::string config_file = "cfg/med.lua"; //standard
    std::string keyset_file = "cfg/keysets.lua"; //standard

    const std::string WINDOW_TEXT = "Lawyer Race";
    int W_WIDTH = 1024; ///<Window Width
    int W_HEIGHT = 768; ///<Window Height

    const int W_BPP = 32;       ///<Window Depth

    const int MAXNUM_OF_PLAYERS = 4; ///< Maximum amount of players that the game supports
    int NUM_OF_PLAYERS = 1;

    const float P_WIDTH = 30.f;     ///<Size of Player sprite width
    const float P_HEIGHT = 30.f;    ///<Size of Player sprite height
    const std::string P_SRC[4] = {"player1", "player2",
                                    "player3", "player4" };

    const float E_WIDTH = 30.f;     ///<Size of Enemy sprite width
    const float E_HEIGHT = 30.f;    ///<Size of Enemy sprite height
    const std::string E_SRC = "enemy";

    const float D_WIDTH = 30.f;     ///<Size of Dollar sprite width
    const float D_HEIGHT = 15.f;    ///<Size of Dollar sprite height
    const std::string D_SRC = "dollar";

    const float MAX_R_WIDTH = 58.f;
    const float MAX_R_HEIGHT = 49.f;

    const float R_WIDTH[3] = {17.f, 26.f, 58.f};
    const float R_HEIGHT[3] = {14.f, 25.f, 49.f};
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
	int MAX_FPS = 200;

	bool SKIP_MENU = false;
} //namespace config