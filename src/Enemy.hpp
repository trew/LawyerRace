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


#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity.hpp"
#include "Player.hpp"

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
