#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity.h"
#include "Player.h"

class Player;
class Enemy: public Entity {
	
public:
	Enemy();
	Enemy(const std::string _fileName);
	Enemy(const std::string _fileName, const int _xPos, const int _yPos);
	virtual ~Enemy();

	virtual void draw(SDL_Surface* _destSurf);
	void handleEvent(SDL_Event& ev);

	void update();
	void updateMovement();
	void updateTarget();
	void updateDirection(Player* player);
	void startMovement();
	void stopMovement();
	void toggleMovement();

private:
	Direction m_direction;
	Player* currentTarget;
	bool m_movingX;
	bool m_movingY;
	int m_diagonalSensitivity;

public:
	static std::list<Enemy*> s_enemyList;
};

#endif
