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


/* The game state */

#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <list>

#include <SDL.h>

#include "Gameconfig.hpp"
#include "Sprite.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Dollar.hpp"
#include "Rock.hpp"
#include "Text.hpp"
#include "FPS.hpp"

#include "AbstractState.hpp"
#include "GameEngine.hpp"

enum InGameState {
    Play = 0,
    CountDown,
    Paused,
    GameOver
};

class GameState: public AbstractState {
public:


    /**
     *  Constructor
     */
    GameState(GameEngine*);


    /**
     *  Destructor
     */
    virtual ~GameState();

    SDL_Window* window;
	SDL_Surface* screenSurface;

public:

    /* STATE FUNCTIONS */

    /**
     *  Initializes the state.
     *
     *  @return True if successful, False otherwise.
     */
    bool Init();


    /**
     *  Cleans up the state before it can be destroyed.
     */
    void Cleanup();


    /**
     *  Update. Called each frame.
     */
    void Update(float timeStep);


    /**
     *  Event handler.
     *
     *  @param Struct with information about the polled event.
     */
    void HandleEvent(SDL_Event &ev);


    /**
     *  Render function. Draws everything to the main screen.
     */
    void Render(float timeAlpha);

	void Pause();

	void Resume();

    /* !STATE FUNCTIONS */

    /* SUPPORTIVE FUNCTIONS */

    /**
     *  Checks if player collides with an enemy or dollars
     *  (powerups is not yet implemented.) 
     *
     *  Takes action accordingly.
     */
    void checkForCollision();


    /**
     *  Creates a dollar and places it randomly on the screen.
     */
    void createDollar();


    /**
     * Creates new enemies
     * Amount of enemies in game is HighestCurrentScore / 5.
     * Example: 1 Player with 10 points       -> ( 10 / 5 = -- 2 Enemies --
     * Example: 2 Players with 9 and 15 points ->( 15 / 5 = -- 3 Enemies --
     */
    void createEnemy();


    /**
     * Creates and removes rocks
     * Amount of rocks in game is                 (HighestCurrentScore - (3 * 5)) / 5 +1
     * Example: 1 Player with 10 points        -> ( 10 - (3 * 5) / 5 +1 = 0 rocks
     * Example: 2 Players with 9 and 15 points -> ( 15 - (3 * 5) / 5 +1 = 1 rocks
     * Example: 1 Player with 25 points        -> ( 25 - (3 * 5) / 5 +1 = 3 rocks
     */
    void createRock();


    /**
     *  Checks if all players are dead.
     *
     *  @return True if all players are dead, False otherwise.
     */
    bool isGameOver();


    /**
     *  Checks the score of all players and retrieves the highest of them.
     *
     *  @return The highest score out of all the players.
     */
    int getHighestCurrentScore();


    /**
     *  Render the result screen.
     *  FIXME
     *  This function is only started.
     */
    void RenderResult();


    /**
     *  Gets a list of all players which has the highest score.
     *
     *  @return a list of player pointers which all has the highest score.
     */
    std::list<Player*> getWinners();


private:
    Player* m_player[4];

    int countDown;
    unsigned int countDown_compareTime;
    InGameState currentInGameState;
    Text* text_countDown;
};

#endif
