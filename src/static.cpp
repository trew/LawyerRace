#ifndef _INIT_STATIC_H_
#define _INIT_STATIC_H_

#include "static.h"

int DIFFICULTY = 2;

const char* const WINDOW_TEXT = "Lawyer Race";
int W_WIDTH = 1024;	///<Window Width
int W_HEIGHT = 768;	///<Window Height

const int W_BPP = 32;		///<Window Depth

const int P_WIDTH = 30;		///<Size of Player sprite width
const int P_HEIGHT = 30;	///<Size of Player sprite height
const char* const P1_SRC = "../../img/player1x30.png";
const char* const P2_SRC = "../../img/player2x30.png";
const char* const P3_SRC = "../../img/player3x30.png";
const char* const P4_SRC = "../../img/player4x30.png";

const int E_WIDTH = 30;		///<Size of Enemy sprite width
const int E_HEIGHT = 30;	///<Size of Enemy sprite height
const char* const E_SRC = "../../img/enemyx30.png";

const int D_WIDTH = 30;		///<Size of Dollar sprite width
const int D_HEIGHT = 15;	///<Size of Dollar sprite height
const char* const D_SRC = "../../img/dollar.png";

const int MAX_R_WIDTH = 58;
const int MAX_R_HEIGHT = 49;
const int R_1_WIDTH = 17;
const int R_1_HEIGHT = 14;
const char* const R_1_SRC = "../../img/stone1-17x14.png";
const int R_2_WIDTH = 26;
const int R_2_HEIGHT = 25;
const char* const R_2_SRC = "../../img/stone2-26x25.png";
const int R_3_WIDTH = 58;
const int R_3_HEIGHT = 49;
const char* const R_3_SRC = "../../img/stone3-58x49.png";

int MAX_ENEMIES = 5;
int ENEMIES_BEFORE_ROCK = 3;
int MAX_ROCKS = 10;

/*!
* SPEED_FACTOR is used in FPS.cpp to control speed of the game. 
* Based on width of screen, because I think it should take the same amount of time to travel from side to side regardless of screensize.
* Tweaks also allows the entities default speed to be 1.0.
*/
float SPEED_FACTOR = (static_cast<float>(W_WIDTH) / 4.0f) * 1.0f;		
const float P_VELOCITY = 1.0f;		///< Player velocity
float E_VELOCITY = 0.4f;		///< Enemy velocity
float R_1_VELOCITY = 1.0f;		///< Rock velocity
float R_2_VELOCITY = 0.75f;	///< Rock velocity
float R_3_VELOCITY = 0.5f;		///< Rock velocity

#endif
