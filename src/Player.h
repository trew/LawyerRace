#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Gameconfig.h"
#include "Entity.h"
#include "Enemy.h"
#include "FPS.h"
#include "Text.h"
#include "KeySet.h"

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
