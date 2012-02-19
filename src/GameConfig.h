#ifndef _GAMECONFIG_H_
#define _GAMECONFIG_H_

class GameConfig
{
public:
	GameConfig() {}
	virtual ~GameConfig() {}

	int difficulty;
	int max_enemies;
	int enemies_before_rock;
	int max_rocks;

	float speed_factor;
	float p_velocity;
	float e_velocity;
	float r_velocity[3];
};


#endif