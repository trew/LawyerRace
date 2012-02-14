#ifndef _INIT_STATIC_H_
#define _INIT_STATIC_H_

extern int DIFFICULTY = 2;

extern const char* const WINDOW_TEXT = "Lawyer Race";
extern int W_WIDTH = 1024;	///<Window Width
extern int W_HEIGHT = 768;	///<Window Height

extern const int W_BPP = 32;		///<Window Depth

extern const int P_WIDTH = 30;		///<Size of Player sprite width
extern const int P_HEIGHT = 30;	///<Size of Player sprite height
extern const char* const P1_SRC = "../../img/player1x30.png";
extern const char* const P2_SRC = "../../img/player2x30.png";
extern const char* const P3_SRC = "../../img/player3x30.png";
extern const char* const P4_SRC = "../../img/player4x30.png";

extern const int E_WIDTH = 30;		///<Size of Enemy sprite width
extern const int E_HEIGHT = 30;	///<Size of Enemy sprite height
extern const char* const E_SRC = "../../img/enemyx30.png";

extern const int D_WIDTH = 30;		///<Size of Dollar sprite width
extern const int D_HEIGHT = 15;	///<Size of Dollar sprite height
extern const char* const D_SRC = "../../img/dollar.png";

extern const int MAX_R_WIDTH = 58;
extern const int MAX_R_HEIGHT = 49;
extern const int R_1_WIDTH = 17;
extern const int R_1_HEIGHT = 14;
extern const char* const R_1_SRC = "../../img/stone1-17x14.png";
extern const int R_2_WIDTH = 26;
extern const int R_2_HEIGHT = 25;
extern const char* const R_2_SRC = "../../img/stone2-26x25.png";
extern const int R_3_WIDTH = 58;
extern const int R_3_HEIGHT = 49;
extern const char* const R_3_SRC = "../../img/stone3-58x49.png";

extern int MAX_ENEMIES = 5;
extern int ENEMIES_BEFORE_ROCK = 3;
extern int MAX_ROCKS = 10;

/*!
* SPEED_FACTOR is used in FPS.cpp to control speed of the game. 
* Based on width of screen, because I think it should take the same amount of time to travel from side to side regardless of screensize.
* Tweaks also allows the entities default speed to be 1.0.
*/
extern float SPEED_FACTOR = (static_cast<float>(W_WIDTH) / 4.0f) * 1.0f;		
extern const float P_VELOCITY = 1.0f;		///< Player velocity
extern float E_VELOCITY = 0.4f;		///< Enemy velocity
extern float R_1_VELOCITY = 1.0f;		///< Rock velocity
extern float R_2_VELOCITY = 0.75f;	///< Rock velocity
extern float R_3_VELOCITY = 0.5f;		///< Rock velocity

#endif