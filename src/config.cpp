#ifndef _INIT_CONFIG_H_
#define _INIT_CONFIG_H_

#include "config.h"
#include "GameConfig.h"

namespace config
{


#ifdef LWPATH 
const std::string path = LWPATH;
#else
const std::string path = ".";
#endif

const std::string WINDOW_TEXT = "Lawyer Race";
int W_WIDTH = 1024;	///<Window Width
int W_HEIGHT = 768;	///<Window Height

const int W_BPP = 32;		///<Window Depth

const int P_WIDTH = 30;		///<Size of Player sprite width
const int P_HEIGHT = 30;	///<Size of Player sprite height
const std::string P_SRC[4] = {path + "/img/player1x30.png", path + "/img/player2x30.png",
								path + "/img/player3x30.png", path + "/img/player4x30.png" };

const int E_WIDTH = 30;		///<Size of Enemy sprite width
const int E_HEIGHT = 30;	///<Size of Enemy sprite height
const std::string E_SRC = path + "/img/enemyx30.png";

const int D_WIDTH = 30;		///<Size of Dollar sprite width
const int D_HEIGHT = 15;	///<Size of Dollar sprite height
const std::string D_SRC = path + "/img/dollar.png";

const int MAX_R_WIDTH = 58;
const int MAX_R_HEIGHT = 49;

const int R_WIDTH[3] = {17, 26, 58};
const int R_HEIGHT[3] = {14, 25, 49};
const std::string R_SRC[3] = {path + "/img/stone1-17x14.png", path +"/img/stone2-26x25.png", path + "/img/stone3-58x49.png"};
	
int DIFFICULTY = 2;
int MAX_ENEMIES = 5;
int ENEMIES_BEFORE_ROCK = 3;
int MAX_ROCKS = 10;

/*!
* SPEED_FACTOR is used in FPS.cpp to control speed of the game. 
* Based on width of screen, because I think it should take the same amount of time to travel from side to side regardless of screensize.
* Tweaks also allows the entities default speed to be 1.0.
*/
float SPEED_FACTOR = (static_cast<float>(W_WIDTH) / 4.0f) * 1.0f;		
float P_VELOCITY = 1.0f;		///< Player velocity
float E_VELOCITY = 0.4f;		///< Enemy velocity

float R_VELOCITY[3] = {1.0f, 0.75f, 0.5f}; //Rock velocities

void loadConfig(const GameConfig &cfg)
{
	MAX_ENEMIES         = cfg.max_enemies;
	ENEMIES_BEFORE_ROCK = cfg.enemies_before_rock;
	MAX_ROCKS           = cfg.max_rocks;
	P_VELOCITY			= cfg.p_velocity;
	E_VELOCITY			= cfg.e_velocity;
	R_VELOCITY[0]		= cfg.r_velocity[0];
	R_VELOCITY[1]		= cfg.r_velocity[1];
	R_VELOCITY[2]		= cfg.r_velocity[2];
}

} //namespace config
#endif
