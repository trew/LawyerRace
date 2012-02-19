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

int DIFFICULTY = 2;

const std::string WINDOW_TEXT = "Lawyer Race";
int W_WIDTH = 1024;	///<Window Width
int W_HEIGHT = 768;	///<Window Height

const int W_BPP = 32;		///<Window Depth

const int P_WIDTH = 30;		///<Size of Player sprite width
const int P_HEIGHT = 30;	///<Size of Player sprite height
const std::string P1_SRC = path + "/img/player1x30.png";
const std::string P2_SRC = path + "/img/player2x30.png";
const std::string P3_SRC = path + "/img/player3x30.png";
const std::string P4_SRC = path + "/img/player4x30.png";

const int E_WIDTH = 30;		///<Size of Enemy sprite width
const int E_HEIGHT = 30;	///<Size of Enemy sprite height
const std::string E_SRC = path + "/img/enemyx30.png";

const int D_WIDTH = 30;		///<Size of Dollar sprite width
const int D_HEIGHT = 15;	///<Size of Dollar sprite height
const std::string D_SRC = path + "/img/dollar.png";

const int MAX_R_WIDTH = 58;
const int MAX_R_HEIGHT = 49;
const int R_1_WIDTH = 17;
const int R_1_HEIGHT = 14;
const std::string R_1_SRC = path + "/img/stone1-17x14.png";
const int R_2_WIDTH = 26;
const int R_2_HEIGHT = 25;
const std::string R_2_SRC = path +"/img/stone2-26x25.png";
const int R_3_WIDTH = 58;
const int R_3_HEIGHT = 49;
const std::string R_3_SRC = path + "/img/stone3-58x49.png";

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
float R_1_VELOCITY = 1.0f;		///< Rock velocity
float R_2_VELOCITY = 0.75f;	///< Rock velocity
float R_3_VELOCITY = 0.5f;		///< Rock velocity

float R_VELOCITY[3];

void loadConfig(const GameConfig &cfg)
{
	MAX_ENEMIES         = cfg.max_enemies;
	ENEMIES_BEFORE_ROCK = cfg.enemies_before_rock;
	MAX_ROCKS           = cfg.max_rocks;
	SPEED_FACTOR        = cfg.speed_factor;
	P_VELOCITY			= cfg.p_velocity;
	E_VELOCITY			= cfg.e_velocity;
	R_VELOCITY[0]		= cfg.r_velocity[0];
	R_VELOCITY[1]		= cfg.r_velocity[1];
	R_VELOCITY[2]		= cfg.r_velocity[2];
}
/*
Easy.difficulty = 1;
Easy.max_enemies = 5;
Easy.enemies_before_rock = 3;
Easy.max_rocks = 10;
Easy.speed_factor = (static_cast<float>(W_WIDTH) / 4.0f) * 1.0f;
Easy.p_velocity = 1.0f;
Easy.e_velocity = 0.4f;
Easy.r_velocity[0] = 1.0f;
Easy.r_velocity[1] = 0.75f;
Easy.r_velocity[2] = 0.5f;

Medium.difficulty = 2;
Medium.max_enemies = 5;
Medium.enemies_before_rock = 3;
Medium.max_rocks = 10;
Medium.speed_factor = (static_cast<float>(W_WIDTH) / 4.0f) * 1.0f;
Medium.p_velocity = 1.0f;
Medium.e_velocity = 0.4f;
Medium.r_velocity[0] = 1.0f;
Medium.r_velocity[1] = 0.75f;
Medium.r_velocity[2] = 0.5f;

Hard.difficulty = 3;
Hard.max_enemies = 5;
Hard.enemies_before_rock = 3;
Hard.max_rocks = 10;
Hard.speed_factor = (static_cast<float>(W_WIDTH) / 4.0f) * 1.0f;
Hard.p_velocity = 1.0f;
Hard.e_velocity = 0.4f;
Hard.r_velocity[0] = 1.0f;
Hard.r_velocity[1] = 0.75f;
Hard.r_velocity[2] = 0.5f;
*/
} //namespace config
#endif
