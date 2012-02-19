#ifndef _GAMECONFIG_H_
#define _GAMECONFIG_H_

#include "config.h"

class GameConfig
{
public:
	GameConfig():
		difficulty(0),
		max_enemies(0),
		enemies_before_rock(0),
		max_rocks(0),
		p_velocity(0.0f),
		e_velocity(0.0f)
		{
			r_velocity[0] = 0.0f;
			r_velocity[1] = 0.0f;
			r_velocity[2] = 0.0f;
		}
	virtual ~GameConfig() {}

	int difficulty;
	int max_enemies;
	int enemies_before_rock;
	int max_rocks;

	float p_velocity;
	float e_velocity;
	float r_velocity[3];
};


#endif