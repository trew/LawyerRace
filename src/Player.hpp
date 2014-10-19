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


/* Player entity */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Gameconfig.hpp"
#include "Entity.hpp"
#include "Enemy.hpp"
#include "FPS.hpp"
#include "Text.hpp"
#include "KeySet.hpp"
#include "TextureRegion.h"

#include <string>

class Player: public Entity {
public:
    Player();
	Player(std::vector<TextureRegion*> regions, KeySet keySet);
	Player(std::vector<TextureRegion*> regions, const float x, const float y, const float w, const float h, KeySet keySet);


    /**
     *  Destructor
     */
    virtual ~Player();


    /**
     *  Loads a keyset to the player
     *
     *  @param set The KeySet instance from which we load keydata.
     */
    void loadKeySet(const KeySet &set);


    /**
     *  Draws the player to a surface.
     *
     *  @param _destSurf Surface the player will be drawn to.
     */
	virtual void render(SDL_Renderer* renderer, float timeAlpha) override;


    /**
     *  Event handler.
     *
     *  @param ev Struct with information about the polled event.
     */
    void handleEvent(SDL_Event& ev);


    /**
     *  Update function. Called every frame.
     *  Moves player according to direction and speed.
     */
    void update(float timeStep) override;


    /**
     *  Sets the direction of the player to be facing UP, DOWN, LEFT or RIGHT.
     *
     *  @param Enum Direction.
     */
    void setDirection(Direction);


    /**
     *  Updates the score text and positions it on the screen.
     */
    void updateScore();


    /**
     *  Increases the score of a player.
     */
    void incScore(int _score);


    /**
     *  Action function that kills the player.
     */
    void kill();


    /**
     *  Checks if the player is dead.
     *
     *  @return True if player is dead, False otherwise.
     */
    bool isDead() const;


    /**
     *  Retrieve the players current score.
     *
     *  @return The players score.
     */
    int getScore() const;

private:
	Direction m_direction{ DOWN };
	int m_score{ 0 };
	Text* score_text{ NULL };
	bool dead{ false };
	int playerNum{ 0 };

    KeySet m_keySet;

public:
    static int alivePlayers;
    static int currentPlayerNum;
};

#endif
