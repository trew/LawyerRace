#ifndef _GAMECONFIG_H_
#define _GAMECONFIG_H_

#include "config.h"

class GameConfig
{
public:
	GameConfig(): //default is easy
		difficulty(1),
		max_enemies(4),
		enemies_before_rock(4),
		max_rocks(10),
		p_velocity(1.0f),
		e_velocity(0.43f)
		{
			r_velocity[0] = 0.9f;
			r_velocity[1] = 0.7f;
			r_velocity[2] = 0.4f;
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