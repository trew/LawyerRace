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


#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <list>

#include <SDL/SDL.h>

#include "Gameconfig.hpp"
#include "Sprite.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Dollar.hpp"
#include "Rock.hpp"
#include "Text.hpp"
#include "FPS.hpp"

#include "AbstractState.hpp"
#include "Game.hpp"

enum InGameState {
	Play = 0,
	CountDown,
	Paused,
	GameOver
};

class GameState: public AbstractState {
public:
	GameState();
	virtual ~GameState();
	int Execute();
	SDL_Surface* mainScreen;

public:
	bool Init();

	void Cleanup();

	void Update();
	void OnEvent(SDL_Event*);
	void Render();

public:
	void checkForCollision();
	void createDollar();
	void createEnemy();
	void createRock();

	bool isGameOver();
	int getHighestCurrentScore();

	void RenderResult();
	std::list<Player*> getWinners();
private:
	bool GameRunning;
	Player* m_player[4];

	int countDown;
	unsigned int countDown_compareTime;
	InGameState currentInGameState;
	Text* text_countDown;

	int temp_delay;


};

#endif
