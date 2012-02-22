#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>
#include "KeySet.h"

///Direction for enemies and player (player uses only DOWN - LEFT)
enum Direction {
	RIGHT  = 0,
	LEFT = 1,
	UP    = 2, 
	DOWN  = 3,
	UP_RIGHT = 4,
	UP_LEFT = 5,
	DOWN_LEFT = 6,
	DOWN_RIGHT = 7,
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

extern const std::string WINDOW_TEXT;

extern int W_WIDTH;	///<Window Width
extern int W_HEIGHT;	///<Window Height

extern const int W_BPP;		///<Window Depth

extern const int MAXNUM_OF_PLAYERS; ///< Maximum amount of players that the game supports
extern int NUM_OF_PLAYERS;

extern const int P_WIDTH;		///<Size of Player sprite width
extern const int P_HEIGHT;	///<Size of Player sprite height
extern const std::string P_SRC[4];

extern const int E_WIDTH;		///<Size of Enemy sprite width
extern const int E_HEIGHT;	///<Size of Enemy sprite height
extern const std::string E_SRC;

extern const int D_WIDTH;		///<Size of Dollar sprite width
extern const int D_HEIGHT;	///<Size of Dollar sprite height
extern const std::string D_SRC;

extern const int MAX_R_WIDTH;
extern const int MAX_R_HEIGHT;
extern const int R_WIDTH[3];
extern const int R_HEIGHT[3];
extern const std::string R_SRC[3];

extern KeySet KEYSET[4];

void loadKeySets();  //load all keysets

extern bool PLAYER_STOP_ENABLED;
extern bool OLD_DIAGONAL_SPEED;

extern int MAX_ENEMIES;
extern int ENEMIES_BEFORE_ROCK;
extern int MAX_ROCKS;

/*!
* SPEED_FACTOR is used in FPS.cpp to control speed of the game. 
* Based on width of screen, because I think it should take the same amount of time to travel from side to side regardless of screensize.
* Tweaks also allows the entities default speed to be 1.0.
*/
extern float SPEED_FACTOR;		
extern float GAME_SPEED;
extern float P_VELOCITY;		///< Player velocity
extern float E_VELOCITY;		///< Enemy velocity
extern float R_VELOCITY[3];		///< Rock velocities

}
#endif
