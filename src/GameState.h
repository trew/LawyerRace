#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <list>

#include <SDL/SDL.h>

#include "Gameconfig.h"
#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "Dollar.h"
#include "Rock.h"
#include "Text.h"
#include "FPS.h"

#include "AbstractState.h"
#include "Game.h"

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
