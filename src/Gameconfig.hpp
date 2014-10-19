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


#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>
#include "KeySet.hpp"

///Direction for enemies and player (player uses only DOWN - LEFT)
enum Direction {
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3,
    UP_RIGHT = 4,
	DOWN_RIGHT = 5,
	DOWN_LEFT = 6,
	UP_LEFT = 7,
    STILL = 8
};

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

namespace config
{

    bool parseConfigFile(std::string _file);
    std::string validateConfigFile(std::string _file);
    std::string validatePath(std::string _path);

    extern std::string path;
    extern std::string config_file;
    extern std::string keyset_file;

    extern const std::string WINDOW_TEXT;

    extern int W_WIDTH; ///<Window Width
    extern int W_HEIGHT;    ///<Window Height

    extern const int W_BPP;     ///<Window Depth

    extern const int MAXNUM_OF_PLAYERS; ///< Maximum amount of players that the game supports
    extern int NUM_OF_PLAYERS;

    extern const float P_WIDTH;       ///<Size of Player sprite width
    extern const float P_HEIGHT;  ///<Size of Player sprite height
    extern const std::string P_SRC[4];

    extern const float E_WIDTH;       ///<Size of Enemy sprite width
    extern const float E_HEIGHT;  ///<Size of Enemy sprite height
    extern const std::string E_SRC;

    extern const float D_WIDTH;       ///<Size of Dollar sprite width
    extern const float D_HEIGHT;  ///<Size of Dollar sprite height
    extern const std::string D_SRC;

    extern const float MAX_R_WIDTH;
    extern const float MAX_R_HEIGHT;
    extern const float R_WIDTH[3];
    extern const float R_HEIGHT[3];
    extern const std::string R_SRC[3];

    extern KeySet KEYSET[4];

    extern bool PLAYER_STOP_ENABLED;
    extern bool OLD_DIAGONAL_SPEED;

    extern int MAX_ENEMIES;
    extern int ENEMIES_BEFORE_ROCK;
    extern int MAX_ROCKS;

    extern float GAME_SPEED;
    extern float P_VELOCITY;        ///< Player velocity
    extern float E_VELOCITY;        ///< Enemy velocity
    extern float R_VELOCITY[3];     ///< Rock velocities

	extern bool ENABLE_LERP;
	extern int MAX_FRAMESKIP;
	extern int MAX_FPS;
}
#endif
