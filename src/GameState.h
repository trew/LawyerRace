#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <list>

#include <SDL.h>

#include "config.h"
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
	void SetupKeySets();

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
	Player* m_player_1;
	KeySet m_p1_keySet;
	
	Player* m_player_2;
	KeySet m_p2_keySet;
	
	Player* m_player_3;
	KeySet m_p3_keySet;
	
	Player* m_player_4;
	KeySet m_p4_keySet;

	int countDown;
	unsigned int countDown_compareTime;
	InGameState currentInGameState;
	Text* text_countDown;

	int temp_delay;


};

#endif
