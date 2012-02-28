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


#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Gameconfig.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"
#include "FPS.hpp"
#include "Text.hpp"
#include "KeySet.hpp"

#include <string>

class Player: public Entity {
public:
	Player();
	Player(const std::string _fileName, KeySet _keySet);
	Player(const std::string _fileName, const int _xPos, const int _yPos , KeySet _keySet);
	virtual ~Player();

	void loadKeySet(const KeySet &set);

	virtual void draw(SDL_Surface* _destSurf);
	void handleEvent(SDL_Event& ev);

	void update();
	void setDirection(Direction);
	void updateScore();
	void incScore(int _score);
	void kill();

	bool isMoving() const;
	bool isDead() const;
	void startMovement();
	void stopMovement();
	void toggleMovement();

	float getXPos();
	float getYPos();
	int getScore() const;

private:
	Direction m_direction;
	int m_score;
	Text* score_text;
	bool dead;
	int playerNum;

	KeySet m_keySet;

public:
	static std::list<Player*> s_playerList;
	static int alivePlayers;
	static int currentPlayerNum;
};

#endif
